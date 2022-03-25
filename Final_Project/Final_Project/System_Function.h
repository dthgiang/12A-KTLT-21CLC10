#pragma once
#include "Menu.h"

typedef void (*drawTxt)();
void drawMenu(string* S, int n, int x, int y, int dis, drawTxt function);

