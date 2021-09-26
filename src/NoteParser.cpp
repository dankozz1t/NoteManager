#include "NoteParser.h"
#include <iostream>
#include <string>
#include <sstream> // strint -> int

NoteParser::NoteParser() { if (!note) note = new Note(); }
NoteParser::~NoteParser() { if (note) delete note; }

Note* NoteParser::parser(std::string dateLine) //Это *****, вызываю клининг бригаду
{
	std::string tag, text, state;
	std::string delimiter; // Проверка на " |"

	 // # ТЭГ | ЗАМЕТКА | СТАТУС | ДЕНЬ.МЕСЯЦ.ГОД | ЧАСЫ.МИНУТЫ | ВАЖНОСТЬ
	// стринг  стринг   INoteStat      tm               tm          bool

	if (dateLine[1] == '!') note->setimportant(true); 
	else note->setimportant(false);

	int i = 6;

	while (delimiter != " |")
	{
		delimiter = "";

		tag += dateLine[i];
		i++;

		delimiter += dateLine[i];
		delimiter += dateLine[i + 1];
	}
	note->setTag(tag);
	i += 3;
	delimiter = "";
	while (delimiter != " |")
	{
		delimiter = "";

		text += dateLine[i];
		i++;

		delimiter += dateLine[i];
		delimiter += dateLine[i + 1];
	}
	note->setText(text);
	i += 2;

	while (dateLine[i] != '|')
	{
		state += dateLine[i];
		i++;
	}

	if (state == " ОТЛОЖЕННАЯ ")
	{
		note->setState(new DeferredNote);
	}
	else if (state == " АКТИВНАЯ ")
	{
		note->setState(new ActiveNote);
	}
	else
	{
		note->setState(new CompletedNote);
	}

	std::string day, month, year, hours, minutes;

	tm date;
	i += 7;

	day += dateLine[++i]; day += dateLine[++i];
	i++;

	month += dateLine[++i]; month += dateLine[++i];
	i++;
	year += dateLine[++i];	year += dateLine[++i];	year += dateLine[++i]; 	year += dateLine[++i];
	i += 3;

	hours += dateLine[++i]; hours += dateLine[++i];
	i++;
	minutes += dateLine[++i]; minutes += dateLine[++i];


	//strint -> int
	std::istringstream(day) >> date.tm_mday;
	std::istringstream(month) >> date.tm_mon;
	std::istringstream(year) >> date.tm_year;
	std::istringstream(hours) >> date.tm_hour;
	std::istringstream(minutes) >> date.tm_min;

	note->setDate(date);

	return note;
}
