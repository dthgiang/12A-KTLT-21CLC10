#pragma once
#include "Graphics.h"


void view_1_student_info_of_course(Data M, int x, int y);
void view_10_student_info_of_course(Data* M, int i, int n, int x, int y);
void view_student_info_of_course(Data* M, int n);


void view_1_course_of_list_course(Course M, int x, int y);
void view_10_course_of_list_course(Course* M, int i, int n, int x, int y);
int view_course_in_year(Course* M, int n, drawTxt fun);