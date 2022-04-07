#pragma once
#include "ConsoleGUI.h"
#include "Graphics.h"
#include "Menu.h"
#include "Staff.h"


typedef Course* (*func_Get_course)(User, SchoolYear, int&);

typedef void (*drawASCII)();

const string csv_tail = ".csv";

const string txt_tail = ".txt";

Course* Read_File_List_Course(User A, SchoolYear SY, int& n);

void read_1_info(User& A, ifstream& f);
//
void read_info(User& A, SchoolYear SY);
//
void read_course(User A, SchoolYear y);
//
void read1CourseInfor(Course& A, ifstream& f);
//
//int get_course(User& A, SchoolYear s_y, int flag = 0);
////
//void Back_A_Semester(SchoolYear& S);
////
//void get_all_course(User& A, SchoolYear SY);
////
//Course* get_course_of_student(User A, SchoolYear SY, int& n);
////
//Data* read_file_student_info_of_course(SchoolYear SY, string IDcourse, int& n);