#pragma once
#include "ConsoleGUI.h"
#include "Graphics.h"
#include "Menu.h"
#include "Staff.h"


typedef Course* (*func_Get_course)(User, SchoolYear, int&);

const string csv_tail = ".csv";

const string txt_tail = ".txt";

Course* Read_File_List_Course(User A, SchoolYear SY, int& n);

