#include <iostream>
#include <Windows.h>

int main()
{
	SetConsoleTitleA("NoteManager");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "");
	
    std::cout << "Планировщик заметок!\n";

	return 0;
}

