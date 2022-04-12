#pragma once
#include <iostream>
#include <fstream>
#include <string>


#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define TAB 9
#define SPACE 8

using namespace std;

struct Mark {
	string ID;
	string Name;
	string C;
	double Total_Mark;
	double Final_Mark;
	double Midterm_Mark;
	double Other_Mark;
};
struct MarkNode {
	Mark data;
	MarkNode* pNext;
};
struct Data {
	int NO_inclass;
	string IDstd;
	string name;
	string sex;
	string Bir;
	string IDsocial;
	string Class;
	MarkNode* phead;
};
struct Course {
	string ID_course;
	string name;
	string teacher;
	int Num_of_creadit;
	int Max_student;
	string Schedule;// thời khóa biểu môn học
	string session[2];//thời gian mỗi tiết học (mỗi môn đều có 2 tiết)
	string DayOfWeek;
	MarkNode* pHead;
};

struct Class {
	string name;
	string MajorClass;
	int Num_of_std_now;
	int Year;//Năm vào trường
};

struct Semester {
	string Name;
	int Num_of_std_now;
	string schoolyear;
	string date_star;
	string date_end;
	Course Course;
	Class Class;
};

struct SchoolYear {
	Semester semester;
	string year;//VD:2020-2021
	int Num_of_std_now;
	string date_star;
	string date_end;
};

//
struct User {
	string ID;
	string Password;
	int role;
	Data info;
};