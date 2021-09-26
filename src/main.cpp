#include <iostream>
#include <Windows.h>
#include "NoteManager.h"

using namespace std;

//TODO:  РЕФАКТОРИНГ: NoteParser::parser (КОСТЫЛЬ РАБОЧИЙ)
//TODO:  ФИКС: При скачке ОТЛОЖЕННЫЕ<->ЗАВЕРШЕННЫЕ два раза просит дату
//TODO:  Навести красоту на функции меню 
//TODO:  При фиксированом окне, нельзя скролить
//TODO:  Функция по сохранения заметок в отдельные файлы
//TODO:  Выбор даты (оставить которая была) при <-> состояния
//TODO:  При выбора даты добавить возможность БЕЗ даты
//TODO: Добавить функцию ОЧИСТИТЬ ВСЁ

//TODO:  UML диаграмму классов

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "");

	SetConsoleTitleA("NoteManager");
	//system("mode con cols=100 lines=30"); //Скролл фикс

	NoteManager* manager = new NoteManager();
	manager->Start();

	return 0;
}

