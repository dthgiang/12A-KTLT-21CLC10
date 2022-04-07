#include "ConsoleGUI.h"

void gotoxy(short int x, short int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE ConsoleHanle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(ConsoleHanle, coord);
}

void textColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void textBgColor(int colorText, int colorBG)//Bg=Background
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (colorBG << 4) | colorText);
}

void drawBoder(int positionX, int positionY, int width, int height, int color)
{
	textBgColor(0, color);
	for (int x = 0; x < width; x++)
	{
		gotoxy(positionX + x, positionY);
		cout << ".";
		gotoxy(positionX + x, positionY + height - 1);
		cout << " ";
	}
	for (int y = 0; y < height; y++)
	{
		gotoxy(positionX, positionY + y);
		cout << " ";
		gotoxy(positionX + width - 1, positionY + y);
		cout << " ";
	}
	gotoxy(44, 0);
	textBgColor(0, color);
}

void drawRectangle(double positionX, double positionY, int width, int height, int color)
{
	textBgColor(0, color);
	gotoxy(positionX, positionY);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			gotoxy(positionX + x, positionY + y);
			cout << " ";
		}
	}
	gotoxy(44, 0);
}

int ReturnX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

int ReturnY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

void hidePointer()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void showPointer()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void DrawTextFile(const char* filename, int x, int y)
{
	fstream file(filename);
	//file.open("character\\test.txt", ios::in);
	if (file.is_open())
	{
		string str;
		while (!file.eof())
		{
			gotoxy(x, y);
			getline(file, str);
			cout << str << endl;
			y++;
		}
	}
	file.close();
}

void printtext(string str, double x, double y) {
	gotoxy(x, y);
	cout << str << endl;
}