#pragma once
#include <ctime>
#include <string>
#include "NoteState.h"


class Note
{
	INoteState* state = nullptr;
	tm date;

	std::string tag;
	std::string text;

	bool important;
public:

	void create();

	std::string printDate();

	std::string print();
	std::string printCompr();

	tm getDate();
	std::string getTag();
	std::string getText();

	bool isImportant();

	std::string currentState();

	void setDate(tm date);
	void setTag(std::string tag);
	void setText(std::string text);
	void setimportant(bool important);
	void setState(INoteState* state);

	void enterDate();
	void enterText();
	void enterTag();

	void next(Note* note);
	void previous(Note* note);
};



