#pragma once
#include <iostream>
#include <fstream>

#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define TAB 9
#define SPACE 8

using namespace std;

/*
Chú thích cho hàm Set Color:
        0 = Black       8 = Gray
        1 = Blue        9 = Light Blue
        2 = Green       10 = Light Green
        3 = Aqua        11 = Light Aqua
        4 = Red         12 = Light Red
        5 = Purple      13 = Light Purple
        6 = Yellow      14 = Light Yellow
        7 = White       15 = Bright White

        Sử dụng công thức i * 16 + j để tạo ra màu mới với
        i là mã màu nền, j là mã màu chữ
        Ví dụ: 2 = 0 * 16 + 2 suy ra wAttributes = 2
        thì màu nền là Black, màu chữ là Green;
        80 = 5 * 16 + 0 suy ra wAttributes = 80
        thì màu nền là Purple, màu chữ là Black.

*/
struct Mark {
	string ID;// linh hoạt trong điểm của sinh viên thì là id môn học, còn trong môn học thì là id sinh viên
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
//struct thông tin học sinh hoặc giáo viên, nếu là giáo viên thì 1 số thông tin bỏ trống
struct Data {
	int NO_inclass;
	string IDstd;
	string name;
	string sex;// 0 là nam, 1 là nữ.
	string Bir;// ngày sinh
	string IDsocial;
	string Class;
	MarkNode* phead;// nhiều môn
};
//
// struct 1 khóa học, 1 số thông tin có thể trống
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
	int role;// 0 là giáo viên quản trị. 1 là học sinh
	Data info;
};