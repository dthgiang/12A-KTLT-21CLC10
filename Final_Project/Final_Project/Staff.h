#pragma once

#define _CRT_SECURE_NO_DEPRECATE

#include "Graphics.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <direct.h>
#include "ConsoleGUI.h"
#include <conio.h>

using namespace std;

typedef void (*fun_show_class)(User, SchoolYear, string);

void DisplayYearSemester(string& Year, string& Semester);

string CheckSem();

void determineYearSemesterNow(string& Year, string& semester);

void addSchoolYear(SchoolYear& Y);

int insertSchoolYear(string& SchoolYear);

void addSemester(string& yearNow, string& semesterNow);

int checkSchoolYear(Semester semester);

void createRegistrationCourse();

void addCourse();

int countLine(string filename);

void drawList(int columnNum, string filename, int y, int indexA[], int indexB[], int line, int flagLine);

void listCourse(User A, string year, string semester);

int insertString(string& data, int limit);

int checkCourseSession();

bool checkTimeEnd(string date, string month, string year);

bool checkTimeStart(string date, string month, string year);

void listClass(User A, SchoolYear Y, fun_show_class Fun);

void showStudentInclass(User user, SchoolYear Y, string classname);

void getLineInfoForStudent(string filename, int line, string column[], int columnNum);

void moveUp(string filename, int& currentLine, int columnNum, int indexB[], int y, string column[], int lineInConsole, int width, int x);

void moveDown(string filename, int& currentLine, int columnNum, int indexB[], int y, string column[], int lineInConsole, int width, int x);