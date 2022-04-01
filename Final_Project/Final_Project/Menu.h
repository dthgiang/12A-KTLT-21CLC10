#pragma once
#include <iostream>
#include "windows.h"
#include <fstream>
#include <string>
#include "Graphics.h"
#include "ConsoleGUI.h"
#include "Graphics.h"
#include "Change_Password.h"
#include "Read_Data.h"
#include "Add_Student.h"

using namespace std;

void DrawFailEnrol();
void DrawEnrolCourse();
void DrawListCourse();
void DrawEditScore();
void DrawStaffMenu(); 
void DrawStudentMenu();
void StaffMenu(User& staff);
void StudentMenu(User& student);
