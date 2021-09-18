#include "Manager.h"
#include <iostream>

void Manager::Create()
{
	Note* note = new Note;

	note->create();

	notes.push_back(note);
}

void Manager::ReadAll()
{
	for (auto& c : notes)
		c->print();

	system("pause");
}

void Manager::Delete()
{
}
