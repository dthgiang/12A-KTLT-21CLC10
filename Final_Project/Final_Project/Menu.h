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

void StaffMenu(User& staff);
void StudentMenu(User& student);

void DrawSuccessfulEnrol();
void DrawFailEnrol();
void DrawEnrolCourse();
void DrawListCourse();
void DrawStaffMenu(); 
void DrawStudentMenu();
void DrawDeleteCourse();
void DrawChangeYear();
void DrawChangeSemester();

void DrawBlank();
