#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include "Graphics.h"

using namespace std;

struct Database {
	string No;
	string ID;
	string name;
	string Birth;
	string sex;
	string IDsocial;
};
Database Input();
int RunMenuCreateClass();
int CheckRowInFile(string filename);
void drawMenuView();
void ImportRandom(string& YearCourse, string& Class);

