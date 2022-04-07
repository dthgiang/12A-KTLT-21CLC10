#pragma once
#include <iostream>
#include "Windows.h"
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include "Graphics.h"


void gotoxy(short int x, short int y);

void textColor(int color);

void textBgColor(int colorText, int colorBG);

void drawRectangle(double positionX, double positionY, int width, int height, int color);

int ReturnX();

int ReturnY();

void hidePointer();

void showPointer();

void drawBoder(int positionX, int positionY, int width, int height, int color);

void FixConsoleWindow();

void DrawTextFile(const char* filename, int x, int y);

void printtext(string str, double x, double y);