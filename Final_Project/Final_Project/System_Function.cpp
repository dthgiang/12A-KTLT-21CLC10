#include "System_Function.h"

void drawMenu(string* S, int n, int x, int y, int dis, drawTxt function)
{
	hidePointer();
	int maxlength = 0;
	maxlength += 1;
	function();

	drawRectangle(x - 10, y, maxlength, n + (n - 1) * dis, 11);
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			drawRectangle(x, y, maxlength - 20, 1, 0);
			textBgColor(15, 0);
			printtext(S[i], x, y + (dis + 1) * i);
		}
		else
			textBgColor(0, 15);
		printtext(S[i], x, y + (dis + 1) * i);
		textBgColor(0, 15);
	}
}

void MoveUp(int X, int& Y, int dis)
{
	Y = Y - (dis + 1);
	gotoxy(X, Y);
}

void MoveDown(int X, int& Y, int dis)
{
	Y = Y + (dis + 1);
	gotoxy(X, Y);
}

int Select(int a, string A[], int _X, int _Y, int dis)
{
	char key;
	int X = _X, Y = _Y;
	int TOP_LIMIT = _Y;
	int BOTTOM_LIMIT = _Y + (dis + 1) * (a - 1);
	int i = 0;
	while (true) {
		key = toupper(_getch());
		if (key == ESC) {
			return -1;
		}
		else {
			if (i >= 0 && i < a && Y <= 23 + a) {
				if (key == UP && Y > TOP_LIMIT) {
					drawRectangle(X, Y, 0, 1, 15);
					gotoxy(X, Y);
					textBgColor(0, 15);
					cout << A[i];
					MoveUp(X, Y, dis);
					i--;
					drawRectangle(X, Y, 0, 1, 0);
					textBgColor(15, 0);
					gotoxy(X, Y);
					cout << A[i];
					textBgColor(0, 15);
				}
				else if (key == DOWN && Y < BOTTOM_LIMIT) {
					drawRectangle(X, Y, 0, 1, 15);
					gotoxy(X, Y);
					textBgColor(0, 15);
					cout << A[i];
					MoveDown(X, Y, dis);
					i++;
					drawRectangle(X, Y, 0, 1, 0);
					textBgColor(15, 0);
					gotoxy(X, Y);
					cout << A[i];
					textBgColor(0, 15);
				}
				else if (key == ENTER) {
					return i;
				}
			}
		}
	}
}
