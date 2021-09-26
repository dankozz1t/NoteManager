#pragma once
#include <string>

#include "Note.h"

class NoteParser
{
	Note* note;
public:
	NoteParser();
	~NoteParser();
	Note* parser(std::string dataLine);
	
};
