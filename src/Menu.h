#pragma once
#include <vector>
#include <iostream>
#include <string>
#include<conio.h>
#include <Windows.h>
#include <winnt.h>

using namespace std;

void ShowConsoleCursor(bool showFlag) // false - Убийца курсора
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

enum ConsoleColor
{
	Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6, LightGray = 7, DarkGray = 8,
	LightBlue = 9, LightGreen = 10, LightCyan = 11, LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};

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
	int textColor;
	int backgroundColor;
public:
	Menu(vector<std::string> menu, int posX, int posY, int textColor=15, int backgroundColor=0)
	: menu(menu), x(posX), y(posY), textColor(textColor), backgroundColor(backgroundColor){}

	int start()
	{
		ShowConsoleCursor(false);
		char c;
		int pos = 0;
		do
		{
			for (int i = 0; i < menu.size(); i++)
			{
				if (i == pos)
				{
					SetColor(backgroundColor, textColor);
					gotoxy(x, y - menu.size() / 2 + i);
					cout <<  "                                                                                          ";
					gotoxy(x, y - menu.size() / 2 + i);
					cout << menu[i] << endl;
					SetColor(textColor, backgroundColor);
				}
				else
				{
					SetColor(textColor, backgroundColor);
					gotoxy(x, y - menu.size() / 2 + i);
					cout << "                                                                                          ";
					gotoxy(x, y - menu.size() / 2 + i);
					cout << menu[i] << endl;
					SetColor(backgroundColor, textColor);
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

		ShowConsoleCursor(true);
		return pos;
	}
	
};
