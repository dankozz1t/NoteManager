#include <iostream>
#include <Windows.h>
#include "Manager.h"


int main()
{
	SetConsoleTitleA("NoteManager");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "");
	
    std::cout << "Планировщик заметок!\n";

	//fdfdfd df 
	Manager* m = new Manager();
	m->ReadAll();



	return 0;
}

