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

void Manager::printAllNote()
{
	for (auto& i : notes)
		i->print();

	system("pause");
}

void Manager::setImportant()
{
	int i = selectNotes();
	importance.push_back(notes[i]);
	notes[i]->tickImportant();
}

void Manager::printImportant()
{
	for (auto& i : importance)
		i->print();

	system("pause");
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

void Manager::editNote()
{
	notes[selectNotes()]->setNote();
}

void Manager::editTag()
{
	notes[selectNotes()]->setTag();
}

void Manager::editDate()
{
	notes[selectNotes()]->setDate();
}

void Manager::deleteNote()
{
	int num = selectNotes();

	if (notes[num]->isImportant())
	{
		for(int i =0; i < importance.size(); i++)
		{
			if(notes[num] == importance[i])
				importance.erase(importance.begin() + i);
		}
	}

	notes.erase(notes.begin() + num);

	
}

