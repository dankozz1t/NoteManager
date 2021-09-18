#include "Note.h"
#include <chrono>
#include <iostream>
#include "LOGS.h"

Note::Note() {}
Note::~Note() {}

std::string Note::getTag() { return tag; }
std::string Note::getNote() { return note; }
std::string Note::getDate() { return date; }
INoteState* Note::getState() { return state; }

void Note::setDateNow(Note* note)
{
	auto end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	date = std::ctime(&end_time);
}

void Note::create()
{
	this->setState(new ActiveNote);

	std::cout << "Введите тэг: # ";
	std::getline(std::cin, this->tag);

	std::cout << "Введите заметку: ";
	std::getline(std::cin, this->note);

	setDateNow(this);
}

void Note::print()
{
	std::cout << "\n * Тэг # " << this->getTag();

	state->printDate(this);
	std::cout << " | --------  --------";
	std::cout << "\n | " << this->getNote();
	std::cout << "\n * --------  --------\n";
}

void Note::setState(INoteState* state)
{
	delete this->state;
	this->state = state;
}

void Note::next(Note* note) { state->next(this); }
void Note::previous(Note* note) { state->previous(this); }


void DeferredNote::printDate(Note* note)
{
	std::cout << " | Дата отстранение: " << note->getDate();
}

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
	note->setDateNow(note);
}

void ActiveNote::printDate(Note* note)
{
#ifdef LOGS
	std::cout << " | Дата создания: " << note->getDate();
#endif
}

void ActiveNote::previous(Note* note)
{
#ifdef LOGS
	std::cout << " Перемещенно в отложенные " << std::endl;
#endif
	note->setState(new DeferredNote);
	note->setDateNow(note);
}


void ActiveNote::next(Note* note)
{
#ifdef LOGS
	std::cout << " Задача завершена (Галочка поставлена) " << std::endl;
#endif
	note->setState(new CompletedNote);
	note->setDateNow(note);
}



void CompletedNote::printDate(Note* note)
{
#ifdef LOGS
	std::cout << " | Дата завершения: " << note->getDate();
#endif
}

void CompletedNote::previous(Note* note)
{
#ifdef LOGS
	std::cout << " Галочка снята " << std::endl;
#endif
	note->setState(new ActiveNote);
	note->setDateNow(note);
}

void CompletedNote::next(Note* note)
{
#ifdef LOGS
	std::cout << " задача и так завершеная" << std::endl;
#endif
}
