#pragma once
#include <map>
#include <ctime>
#include <list>
#include <string>
#include <vector>

#include "Note.h"


class Manager
{
	 std::vector<Note*> notes;

public:
	void create();
	void readAll();
	
};
