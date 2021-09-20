#pragma once
#include <vector>
#include <iostream>
#include <string>
#include<conio.h>
#include <Windows.h>
#include <winnt.h>

using namespace std;

void SetColor(int text = 7, int background = 0)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void gotoxy(int x, int y, int sizeLen = 0, int sizeHeight = 100) //При наличии размера строки выполняется форматирование по центру
{
	if (sizeLen)
		x = (x + sizeHeight - sizeLen) / 2;

	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

enum KeyboardKey
{
	Up = 72, Down = 80, Right = 77, Left = 75, Enter = 13, Space = 32, Esc = 27
};

class Menu
{
	vector<std::string> menu;
	int x;
	int y;
public:
	Menu(vector<std::string> menu, int posX, int posY) : menu(menu), x(posX), y(posY){}

	int start()
	{
		char c;
		int pos = 0;
		do
		{
			for (int i = 0; i < menu.size(); i++)
			{
				if (i == pos)
				{
					SetColor(0, 15);
					gotoxy(x, y - menu.size() / 2 + i);
					cout <<  "                                                                                         ";
					gotoxy(x, y - menu.size() / 2 + i);
					cout << menu[i] << endl;
					SetColor(15, 0);
				}
				else
				{
					SetColor(15, 0);
					gotoxy(x, y - menu.size() / 2 + i);
					cout << "                                                                                         ";
					gotoxy(x, y - menu.size() / 2 + i);
					cout << menu[i] << endl;
					SetColor(0, 15);
				}

			}
			c = _getch();
			switch (c)
			{
			case Up:
				if (pos > 0)
					pos--;
				break;
			case Down:
				if (pos < menu.size() - 1)
					pos++;
				break;
			case Enter:
				break;
			default:
				break;
			}
		} while (c != 13);
		SetColor(7, 0);
		return pos;
	}
	
};
