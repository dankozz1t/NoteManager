#pragma once
#include <vector>

#include "Note.h"


class Manager
{
	 std::vector<Note*> notes;
public:
	void Create();
	void ReadAll();
	void Delete();
	
};
