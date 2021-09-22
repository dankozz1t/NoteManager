#include "Manager.h"
#include <string>
#include <map>
#include <iostream>

#include "Menu.h"

void Manager::createNote()
{
	Note* note = new Note;

	note->create();

	notes.push_back(note);
}

void Manager::printAllNotes()
{
	printImportant();
	printActivated();
	printDeferrend();
	printCompleted();
}

void Manager::printNotes(std::string type, int color)
{
	for (auto& i : notes)
	{
		if (i->currentState() != type) continue;

		SetColor(color, 0);
		i->print();
	}
}

void Manager::printDeferrend() { printNotes("DeferredNote", 7); }
void Manager::printActivated() { printNotes("ActiveNote", 15); }
void Manager::printCompleted() { printNotes("CompletedNote", 8); }

void Manager::printImportant()
{
	for (auto& i : importance)
	{
		SetColor(6, 0);
		i->print();
	}
}

void Manager::markAsImportant()
{
	int i = selectNotes();
	importance.push_back(notes[i]);
	notes[i]->markAsImportant();
}


int Manager::selectNotes()
{
	system("cls");
	std::cout << "ВЫБЕРЕТЕ ЗАМЕТКУ: " << std::endl;
	std::vector<std::string> menuNotes;

	for (auto& i : notes)
		menuNotes.push_back(i->printS());

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

