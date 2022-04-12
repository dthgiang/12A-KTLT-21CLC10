#pragma once
#include <iostream>
#include "Graphics.h"
#include "Menu.h"
#include "Login.h"

typedef void (*drawTXT)();
typedef Course* (*func_Get_course)(User, SchoolYear, int&);

void drawMenu(string* S, int n, int x, int y, int dis, drawTXT fun);

void MoveUp(int X, int& Y, int dis);

void MoveDown(int X, int& Y, int dis);

int Select(int a, string A[], int _X, int _Y, int dis);

void enroll_course(User& user, SchoolYear SchYr);

void change_Year_Semester(SchoolYear& S);

void DisPlay_Course_Of_Student(SchoolYear Y, User A);

void delete_course(User& A, SchoolYear s_y);

void viewStudentInCourse(User user, SchoolYear SY);

void Output_info(User A);//

void view_1_course_of_list_course(Course M, int x, int y);

void view_10_course_of_list_course(Course* M, int i, int n, int x, int y);

int view_course_in_year(Course* M, int n, drawTXT fun);

Course* select_course(User A, SchoolYear SY, func_Get_course fun, drawTXT fundraw);

void view_1_student_info_of_course(Data M, int x, int y);

void view_10_student_info_of_course(Data* M, int i, int n, int x, int y);

void view_student_info_of_course(Data* M, int n);

void rewrite_course_of_student_file(User user, string fileName, string data, int command_flag);
//hàm ghi danh vào file khóa học tổng của staff, user là học sinh.
void rewrite_course_file(User user, string fileName, int command_flag);