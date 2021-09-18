#include <iostream>
#include <Windows.h>
#include "Manager.h"

// This is Drewsovsky's comment
int main()
{
	SetConsoleTitleA("NoteManager");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "");
	
    std::cout << "Планировщик заметок!\n";


	Manager* m = new Manager();
	m->create();
	m->create();
	m->create();
	m->create();
	m->create();
	m->create();
	m->create();
	m->readAll();



	return 0;
}

