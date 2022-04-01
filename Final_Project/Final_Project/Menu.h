#pragma once
#include <iostream>
#include "windows.h"
#include <fstream>
#include <string>
#include "Graphics.h"
#include "ConsoleGUI.h"
#include "Graphics.h"

using namespace std;

void DrawListCourse();
void DrawEditScore();
void DrawStaffMenu(); 
void DrawStudentMenu();
void StaffMenu(User& staff);
void StudentMenu(User& student);
