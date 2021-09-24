#include "Manager.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include "Menu.h"

void Manager::Load()
{

}

void Manager::Save()
{

	ofstream out("Save\\AllNotes.txt"); //имена и количесво аккаунтов
	if (out.is_open())
	{
		out << notes.size() << endl;
		for (size_t i = 0; i < notes.size(); i++)
		{
			out << notes[i]->printCompr();
		}
	}
	out.close();

	for (size_t i = 0; i < notes.size(); i++)
	{

		std::string nameFile = "Save\\";
		nameFile += notes[i]->currentState();
		nameFile += ".txt";

		cout << nameFile << endl;

		ofstream out(nameFile);
		if (out.is_open())
		{
			out << printNotes(notes[i]->currentState(), 0) << endl;

		}
		out.close();
	}

}

void Manager::createNote()
{
	Note* note = new Note;

	note->create();

	notes.push_back(note);
}

void Manager::printAllNotes()
{
	std::cout << printImportant();
	std::cout << printActivated();
	std::cout << printDeferrend();
	std::cout << printCompleted();
}

std::string Manager::printNotes(std::string type, int color)
{
	std::string st;
	for (auto& i : notes)
	{
		if (i->currentState() != type) continue;
		if (i->isImportant() && color != 0) continue;

		//Если color = 0, значит его вызывают для сохранения файла, сохраняет он сжатую версию.
		if(color != 0) { SetColor(color, 0); st += i->print();}
		else st += i->printCompr();
	}
	return st;
}


std::string  Manager::printDeferrend() { return printNotes("DeferredNote", 7); }
std::string Manager::printActivated() { return printNotes("ActiveNote", 15); }
std::string  Manager::printCompleted() { return  printNotes("CompletedNote", 8); }

std::string  Manager::printImportant()
{
	std::string st;
	for (auto& i : importance)
	{
		SetColor(6, 0);
		st += i->print();
	}
	return st;
}

void Manager::markAsImportant()
{
	int i = selectNotes();
	importance.push_back(notes[i]);
	notes[i]->markAsImportant();
}

void Manager::dateSearch()
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

void Manager::tagSearch()
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

void Manager::noteSearch()
{
	std::string noteBuff;
	std::cout << "Введите заметку: ";
	std::getline(std::cin, noteBuff);

	for (auto& i : notes)
	{
		if (i->getNote() == noteBuff)
		{
			cout << i->print();
		}
	}
}


int Manager::selectNotes()
{
	system("cls");
	std::cout << "ВЫБЕРЕТЕ ЗАМЕТКУ: " << std::endl;
	std::vector<std::string> menuNotes;

	for (auto& i : notes)
		menuNotes.push_back(i->printCompr());

	Menu mN(menuNotes, 1, 3);

	return mN.start();
}

void Manager::previousNote() { int num = selectNotes(); notes[num]->previous(notes[num]); }
void Manager::nextNote() { int num = selectNotes(); notes[num]->next(notes[num]); }


void Manager::editNote() { notes[selectNotes()]->setNote(); }

void Manager::editTag() { notes[selectNotes()]->setTag(); }

void Manager::editDate() { notes[selectNotes()]->setDate(); }


void Manager::deleteNote()
{
	int num = selectNotes();
	if (notes[num]->isImportant())
	{
		for (int i = 0; i < importance.size(); i++)
		{
			if (notes[num] == importance[i])
				importance.erase(importance.begin() + i);
		}
	}
	notes.erase(notes.begin() + num);
}

