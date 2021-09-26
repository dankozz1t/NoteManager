#include "NoteState.h"
#include <iostream>
#include "LOGS.h"
#include "Note.h"

//---------------DeferredNote------------

std::string DeferredNote::currentState(){ return "ОТЛОЖЕННАЯ"; }

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
	note->enterDate();
}


//---------------ActiveNote------------

std::string ActiveNote::currentState() { return "АКТИВНАЯ"; }

void ActiveNote::previous(Note* note)
{
#ifdef LOGS
	std::cout << " Перемещенно в отложенные " << std::endl;
#endif
	note->setState(new DeferredNote);
	note->setimportant(false);
	note->enterDate();
}

void ActiveNote::next(Note* note)
{
#ifdef LOGS
	std::cout << " Задача завершена (Галочка поставлена) " << std::endl;
#endif
	note->setState(new CompletedNote);
	note->setimportant(false);
	note->enterDate();
}


//---------------CompletedNote------------

std::string CompletedNote::currentState() { return "ЗАВЕРШЕННОЕ"; }

void CompletedNote::previous(Note* note)
{
#ifdef LOGS
	std::cout << " Галочка снята " << std::endl;
#endif
	note->setState(new ActiveNote);
	note->enterDate();
}

void CompletedNote::next(Note* note)
{
#ifdef LOGS
	std::cout << " задача и так завершеная" << std::endl;
#endif
}
