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


	Manager* m = new Manager();
	m->createNote();
	//m->createNote();
	//m->createNote();
	//
	//m->setImportant();
	m->setImportant();

	//m->deleteNote();


	cout << "\nПринт важные: " << endl;
	m->printImportant();

	cout << "\nПринт все: "<< endl;
	m->printAllNote();




	return 0;
}

