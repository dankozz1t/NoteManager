﻿#include "Note.h"
#include <Windows.h>
#include <iostream>
#include "LOGS.h"

void Note::create()
{
	this->setState(new ActiveNote);
	important = false;

	std::cout << "\nВведите тэг: # ";
	std::getline(std::cin, this->tag);

	std::cout << "Введите заметку: ";
	std::getline(std::cin, this->note);

	setDate();
}

bool Note::isImportant() { return important; }
void Note::markAsImportant() { important = true; }

void Note::printDate()
{
	if (date.tm_mday < 10) std::cout << "0";
	std::cout << date.tm_mday << '.';
	if (date.tm_mon < 10) std::cout << "0";
	std::cout << date.tm_mon << '.';
	std::cout << date.tm_year << " | ";
	if (date.tm_hour < 10) std::cout << "0";
	std::cout << date.tm_hour << ':';
	if (date.tm_min < 10) std::cout << "0";
	std::cout << date.tm_min << std::endl;
}

std::string Note::printDateS()
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
	str += std::to_string(date.tm_min); str += "\n";

	return str;
}


void Note::print()
{
	std::cout << "\n * Тэг # " << tag;

	state->printDate(this);
	std::cout << " | --------  --------";
	std::cout << "\n | " << note;
	std::cout << "\n * --------  --------\n";
}

std::string Note::printS()
{
	return std::string("# " + tag + " | " + note + " | " + printDateS());
}


void Note::setDate()
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

void Note::setNote()
{
	std::cout << "Введите заметку: ";
	std::getline(std::cin, this->note);
}

void Note::setTag()
{
	std::cout << "\nВведите тэг: # ";
	std::getline(std::cin, this->tag);
}

void Note::setState(INoteState* state)
{
	if (this->state) delete this->state;
	this->state = state;
}

std::string Note::currentState() { return state->currentState(); }

void Note::next(Note* note) { state->next(this); }
void Note::previous(Note* note) { state->previous(this); }



void DeferredNote::printDate(Note* note)
{
	std::cout << " | ОТЛОЖЕННАЯ | Дата: "; note->printDate();
}

std::string DeferredNote::currentState() { return "DeferredNote"; }

void DeferredNote::previous(Note* note)
{
#ifdef LOGS
	std::cout << " Задача и так в отложеных " << std::endl;
#endif
}

void DeferredNote::next(Note* note)
{
#ifdef LOGS
	std::cout << " Перемещенно в активные " << std::endl;
#endif

	note->setState(new ActiveNote);
	note->setDate();
}



void ActiveNote::printDate(Note* note)
{
	std::cout << " | АКТИВНАЯ | Дата: "; note->printDate();
}

std::string ActiveNote::currentState() { return "ActiveNote"; }

void ActiveNote::previous(Note* note)
{
#ifdef LOGS
	std::cout << " Перемещенно в отложенные " << std::endl;
#endif
	note->setState(new DeferredNote);
	note->setDate();
}

void ActiveNote::next(Note* note)
{
#ifdef LOGS
	std::cout << " Задача завершена (Галочка поставлена) " << std::endl;
#endif
	note->setState(new CompletedNote);
	note->setDate();
}



void CompletedNote::printDate(Note* note)
{
	std::cout << " | ЗАВЕРШЕННОЕ | Дата: "; note->printDate();
}

std::string CompletedNote::currentState() { return "CompletedNote"; }

void CompletedNote::previous(Note* note)
{
#ifdef LOGS
	std::cout << " Галочка снята " << std::endl;
#endif
	note->setState(new ActiveNote);
	note->setDate();
}

void CompletedNote::next(Note* note)
{
#ifdef LOGS
	std::cout << " задача и так завершеная" << std::endl;
#endif
}
