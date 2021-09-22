#pragma once
#include <vector>
#include "Note.h"

class Manager
{
	 std::vector<Note*> notes;
	 std::vector<Note*> importance;

	 int selectNotes();
	 void printNotes(std::string type, int color);

public:

	void createNote();

	void printAllNotes();

	void printDeferrend();
	void printActivated();
	void printCompleted();

	void printImportant();
	void markAsImportant();

	void previousNote();
	void nextNote();

	void editNote();
	void editTag();
	void editDate();

	void deleteNote();
	
};
