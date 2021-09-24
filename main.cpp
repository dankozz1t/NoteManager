#include <iostream>
#include <Windows.h>
#include "Manager.h"

#include <fstream>
using namespace std;

int main()
{
	SetConsoleTitleA("NoteManager");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "");


	Manager* manager = new Manager();
	manager->createNote();
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


	cout << "\nПринт все: " << endl;
	manager->printAllNotes();
	//
	//cout << "\nПринт активные: " << endl;
	//manager->printActivated();


	//cout << "\nПоиск по дате: " << endl;
	//manager->dateSearch();

	//cout << "\nПринт все: "<< endl;
	//manager->printAllNotes();
	manager->Save();



	return 0;
}

