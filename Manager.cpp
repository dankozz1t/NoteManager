#include "Manager.h"
#include <string>
#include <map>
#include <iostream>

void Manager::create()
{
	Note* note = new Note;

	note->create();

	notes.push_back(note);
}

void Manager::readAll()
{

	for (auto& c : notes)
		c->print();

	system("pause");
}
