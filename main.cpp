#include <iostream>
#include <Windows.h>
#include "Manager.h"

using namespace std;

int main()
{
	SetConsoleTitleA("NoteManager");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "");


	Manager* manager = new Manager();
	manager->createNote();

	cout << "\nСоздание и в отложегын: " << endl;
	manager->createNote();
	manager->previousNote();

	cout << "\nСоздание и в Завершенные: " << endl;
	manager->createNote();
	manager->nextNote();


	cout << "\nСоздание и отметить как важное: " << endl;
	manager->createNote();
	manager->markAsImportant();

	cout << "\nПринт активные: " << endl;
	manager->printActivated();

	cout << "\nПринт все: "<< endl;
	manager->printAllNotes();




	return 0;
}

