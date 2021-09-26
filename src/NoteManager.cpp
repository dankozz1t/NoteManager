#include "NoteManager.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "NoteParser.h"

void NoteManager::Load()
{
	ifstream in("Save\\AllNotes.txt"); //Все заметки

	if (in.is_open())
	{
		std::string lineNote;

		NoteParser* notePars;
		while (std::getline(in, lineNote))
		{
			notePars = new NoteParser();
			notes.push_back(notePars->parser(lineNote));
			lineNote = "";
		}
	}

}

void NoteManager::Save()
{
	ofstream out("Save\\AllNotes.txt"); //Все заметки
	if (out.is_open())
	{
		for (size_t i = 0; i < notes.size(); i++)
		{
			out << notes[i]->printCompr();
			out << std::endl;
		}
	}
	out.close();

	//for (size_t i = 0; i < notes.size(); i++) //Каждое состоние в каждый отдельный файл
	//{
	//	std::string nameFile = "Save\\";
	//	nameFile += notes[i]->currentState();
	//	nameFile += ".txt";

	//	ofstream out(nameFile);
	//	if (out.is_open())
	//	{
	//		out << printNotes(notes[i]->currentState(), 0) << endl;
	//		out << notes[i]->isImportant();
	//		out << "\n";
	//	}
	//	out.close();
	//}
}

void NoteManager::createNote()
{
	Note* note = new Note;

	note->create();

	notes.push_back(note);
}

void NoteManager::printAllNotes()
{
	std::cout << printImportant();
	std::cout << printActivated();
	std::cout << printDeferrend();
	std::cout << printCompleted();
}

std::string NoteManager::printNotes(std::string type, int color)
{
	std::string st;
	for (auto& i : notes)
	{
		if (i->currentState() != type) continue;
		if (i->isImportant()) { continue; }

		//Если color == Black (0), значит его вызывают для сохранения файла, сохраняет он сжатую версию заметки.
		if (color != Black) { SetColor(color, Black); st += i->print(); }
		else st += i->printCompr() + "\n";
	}
	return st;
}

void NoteManager::Start()
{
	Load();
	vector<string> menuUser = { "* Создать заметку",
 "* Редактировать...", "    Редактировать полностью", "    Редактировать заметку", "    Редактировать тэг","    Редактировать дату",
 "* Поставить галочку <Важное>",
 "* Снять галочку <Важное>",
 "* Переместить в...", "    Переместить в отложенные", "    Переместить в активные", "    Переместить в завершенные",
 "* Посмотреть...", "    Посмотреть все", "    Посмотреть отложенные", "    Посмотреть активные", "    Посмотреть завершенные", "    Посмотреть важные",
 "* Поиск по...", "    Поиск по дате", "    Поиск по тэгу", "    Поиск по записке",
 "* Удалить заметку",
 "* Сохранить",
 "* Выход" };
	SetColor(Yellow, Black);
	Menu mN(menuUser, 5, 14, LightCyan);

	int num;
	do
	{
		system("cls");

		cout << "    "; SetColor(Yellow, Magenta);
		cout << "                                      ПЛАНИРОВЩИК ЗАДАЧ                                     \n";
		gotoxy(4, 28); 
		cout << "                                                                                           \n";

		num = mN.start();

		system("cls");
		switch (num)
		{
		case 0: createNote(); break;
		case 1: //Редактировать...
		case 2: edit(); break;
		case 3: editNote(); break;
		case 4: editTag(); break;
		case 5: editDate(); break;
		case 6: putAsImportant(); break;
		case 7: removeAsImportant(); break;
		case 8: //Переместить...
		case 9:  move("ОТЛОЖЕННАЯ"); break;
		case 10:  move("АКТИВНАЯ"); break;
		case 11:  move("ЗАВЕРШЕННОЕ"); break;
		case 12: //Показать...
		case 13: printAllNotes(); break;
		case 14: std::cout << printDeferrend();  break;
		case 15: std::cout << printImportant(); std::cout << printActivated(); break;
		case 16: std::cout << printCompleted(); break;
		case 17: std::cout << printImportant(); break;
		case 18: //Поиск по...
		case 19: dateSearch();  break;
		case 20: tagSearch();   break;
		case 21: textSearch(); break;
		case 22: deleteNote();  break;
		case 23: Save(); break;
		}
		system("pause");
	} while (num != 24);
	Save();
}


std::string  NoteManager::printDeferrend() { return printNotes("ОТЛОЖЕННАЯ", LightGray); }
std::string NoteManager::printActivated() { return printNotes("АКТИВНАЯ", White); }
std::string  NoteManager::printCompleted() { return  printNotes("ЗАВЕРШЕННОЕ", DarkGray); }

std::string  NoteManager::printImportant()
{
	std::string st;
	for (auto& i : notes)
	{
		if (i->isImportant())
		{
			SetColor(Brown, Black);
			st += i->print();
		}
	}
	return st;
}

void NoteManager::putAsImportant() { notes[selectNotes()]->setimportant(true); }
void NoteManager::removeAsImportant() { notes[selectNotes()]->setimportant(false); }

void NoteManager::move(std::string stateDesired)
{
	int num = selectNotes();
	std::string stateNow = notes[num]->currentState();

	if(stateNow == stateDesired)
	{
		cout << "Заметка уже " << stateDesired << endl;
	}
	else if(stateNow == "ОТЛОЖЕННАЯ")
	{
		if (stateDesired == "АКТИВНАЯ") notes[num]->next(notes[num]);
		if (stateDesired == "ЗАВЕРШЕННОЕ") { notes[num]->next(notes[num]);  notes[num]->next(notes[num]); }
		cout << "Теперь я " << stateDesired << endl;;
	}
	else if (stateNow == "АКТИВНАЯ")
	{
		if (stateDesired == "ОТЛОЖЕННАЯ") notes[num]->previous(notes[num]);
		if (stateDesired == "ЗАВЕРШЕННОЕ") { notes[num]->next(notes[num]); }
		cout << "Теперь я " << stateDesired << endl;;
	}
	else if(stateNow == "ЗАВЕРШЕННОЕ")
	{
		if (stateDesired == "АКТИВНАЯ") notes[num]->previous(notes[num]);
		if (stateDesired == "ОТЛОЖЕННАЯ") { notes[num]->previous(notes[num]);  notes[num]->next(notes[num]); }
		cout << "Теперь я " << stateDesired << endl;
	}

}

void NoteManager::dateSearch()
{
	tm dateBuff;
	std::cout << std::endl;
	std::cout << "День: ";  std::cin >> dateBuff.tm_mday;
	std::cout << "Месяц: "; std::cin >> dateBuff.tm_mon;
	std::cout << "Год: "; std::cin >> dateBuff.tm_year;

	for (auto& i : notes)
	{
		if (i->getDate().tm_mday == dateBuff.tm_mday
			&& i->getDate().tm_mon == dateBuff.tm_mon
			&& i->getDate().tm_year == dateBuff.tm_year)
		{
			cout << i->print();
		}
	}

}

void NoteManager::tagSearch()
{
	std::string tagBuff;
	std::cout << "\nВведите тэг: # ";
	std::getline(std::cin, tagBuff);

	for (auto& i : notes)
	{
		if (i->getTag() == tagBuff)
		{
			cout << i->print();
		}
	}
}

void NoteManager::textSearch()
{
	std::string noteBuff;
	std::cout << "Введите заметку: ";
	std::getline(std::cin, noteBuff);

	for (auto& i : notes)
	{
		if (i->getText() == noteBuff)
		{
			cout << i->print();
		}
	}
}


int NoteManager::selectNotes()
{
	system("cls");
	std::cout << "\n ВЫБЕРЕТЕ ЗАМЕТКУ: " << std::endl;
	std::vector<std::string> menuNotes;

	for (auto& i : notes)
		menuNotes.push_back(i->printCompr());

	Menu mN(menuNotes, 1, 8);

	return mN.start();
}


void NoteManager::edit()
{
	int numNote = selectNotes();

	notes[numNote]->enterTag();
	notes[numNote]->enterText();
	notes[numNote]->enterDate();
}


void NoteManager::editNote() { notes[selectNotes()]->enterText(); }

void NoteManager::editTag() { notes[selectNotes()]->enterTag(); }

void NoteManager::editDate() { notes[selectNotes()]->enterDate(); }


void NoteManager::deleteNote() { notes.erase(notes.begin() + selectNotes()); }

