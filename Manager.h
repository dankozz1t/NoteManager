#pragma once

#include <vector>

#include "Note.h"


class Manager
{
	 std::vector<Note*> notes;
	 std::vector<Note*> importance;

public:
	void createNote();
	void printAllNote();
	
	//void printNoteTAG(std::string);
	//void printNoteDeferred();
	//void printNoteActive();
	//void printNoteComleted();
	
	void setImportant();
	void printImportant();

	int selectNotes();
	
	void editNote();
	void editTag();
	void editDate();
	void deleteNote();
	
};
