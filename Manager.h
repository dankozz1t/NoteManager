#pragma once
#include <vector>
#include "Note.h"

class Manager
{
	 std::vector<Note*> notes;
	 std::vector<Note*> importance;

	 int selectNotes();
	 std::string printNotes(std::string type, int color);

public:

	void Load();
	void Save();

	void createNote();

	void printAllNotes();

	std::string  printDeferrend();
	std::string printActivated();
	std::string  printCompleted();

	std::string  printImportant();
	void markAsImportant();

	void dateSearch();
	void tagSearch();
	void noteSearch();


	void previousNote();
	void nextNote();

	void editNote();
	void editTag();
	void editDate();

	void deleteNote();
	
};
