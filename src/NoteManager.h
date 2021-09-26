#pragma once
#include <vector>
#include "Note.h"

class NoteManager
{
	 std::vector<Note*> notes;

	 int selectNotes();
	 std::string printNotes(std::string type, int color);

public:

	void Start();

	void Load();
	void Save();

	void createNote();

	void printAllNotes();

	std::string  printDeferrend();
	std::string printActivated();
	std::string  printCompleted();

	std::string  printImportant();
	void putAsImportant();
	void removeAsImportant();

	void dateSearch();
	void tagSearch();
	void textSearch();

	void move(std::string stateDesired);

	void edit();
	void editNote();
	void editTag();
	void editDate();

	void deleteNote();
	
};
