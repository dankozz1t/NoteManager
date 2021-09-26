#include "Note.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "NoteState.h"

void Note::create()
{
	this->setState(new ActiveNote);
	important = false;

	std::cout << "\nВведите тэг: # ";
	std::getline(std::cin, this->tag);

	std::cout << "Введите заметку: ";
	std::getline(std::cin, this->text);

	enterDate();
}

bool Note::isImportant() { return important; }

std::string Note::printDate()
{
	std::string str;
	if (date.tm_mday < 10) str += "0";
	str += std::to_string(date.tm_mday); str += '.';
	if (date.tm_mon < 10) str += "0";
	str += std::to_string(date.tm_mon); str += '.';
	str += std::to_string(date.tm_year); str += " | ";
	if (date.tm_hour < 10)str += "0";
	str += std::to_string(date.tm_hour); str += ':';
	if (date.tm_min < 10) str += "0";
	str += std::to_string(date.tm_min);

	return str;
}


std::string Note::print()
{
	std::string noteST;
	if (important) noteST += "\n [!] ";
	else noteST += "\n [ ] ";

	noteST += "Тэг # " + tag;
	noteST += " | ";
	noteST += state->currentState();
	noteST += " | Дата: " + printDate();
	noteST += "\n | --------  --------";
	noteST += "\n | " + text;
	noteST += "\n * --------  --------\n";
	return noteST;
}

std::string Note::printCompr()
{
	std::string noteST;
	if (important) noteST += "[!] ";
	else noteST += "[ ] ";
	noteST+= "# " + tag + " | " + text + " | " + state->currentState() + " | Дата: " + printDate();
	return  noteST;
}

tm Note::getDate() { return date; }
std::string Note::getTag() { return tag; }
std::string Note::getText() { return text; }

void Note::setDate(tm date) { this->date = date; }
void Note::setTag(std::string _tag) { tag = _tag; }
void Note::setText(std::string text) { this->text = text; }
void Note::setimportant(bool important) { this->important = important; }

void Note::enterDate()
{
	std::cout << "0 - Поставить дату сейчас | 1 - Ввести свою дату " << std::endl;
	bool menu; std::cout << "Введите: ";  std::cin >> menu;
	if (menu)
	{
		std::cout << std::endl;
		std::cout << "День: ";  std::cin >> date.tm_mday;
		std::cout << "Месяц: "; std::cin >> date.tm_mon;
		std::cout << "Год: "; std::cin >> date.tm_year;

		std::cout << "Час: "; std::cin >> date.tm_hour;
		std::cout << "Минуты: "; std::cin >> date.tm_min;
	}
	else
	{
		time_t t = time(0);
		date = *localtime(&t);
		date.tm_year += 1900;
		date.tm_mon += 1;
	}
	std::cin.ignore();
}

void Note::enterText()
{
	std::cout << "Введите заметку: ";
	std::getline(std::cin, this->text);
}

void Note::enterTag()
{
	std::cout << "\nВведите тэг: # ";
	std::getline(std::cin, this->tag);
}

void Note::setState(INoteState* state) { this->state = state; }

std::string Note::currentState() { return state->currentState(); }

void Note::next(Note* note) { state->next(this); }
void Note::previous(Note* note) { state->previous(this); }

