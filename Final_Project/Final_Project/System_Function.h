#pragma once
#include "Menu.h"
#include "Graphics.h"
#include "Login.h"

typedef void (*drawTxt)();
void drawMenu(string* S, int n, int x, int y, int dis, drawTxt function);
void MoveUp(int X, int& Y, int dis);
void MoveDown(int X, int& Y, int dis);
int Select(int a, string A[], int _X, int _Y, int dis);

