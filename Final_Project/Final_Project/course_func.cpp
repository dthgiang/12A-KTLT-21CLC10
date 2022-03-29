#include "course_func.h"

void view_1_student_info_of_course(Data M, int x, int y) {
	printtext(to_string(M.NO_inclass), x, y);
	printtext(M.IDstd, x + 7, y);
	printtext(M.name, x + 35, y);
	printtext(M.Bir, x + 57, y);
	printtext(M.sex, x + 80, y);
	printtext(M.IDsocial, x + 90, y);
}

void view_10_student_info_of_course(Data* M, int i, int n, int x, int y) {
	if (n - i >= 10) {
		for (int j = 0; j < 10; j++) {
			view_1_student_info_of_course(M[i + j], x, y + j);
		}
	}
	else {
		for (int j = 0; j < n - i; j++) {
			view_1_student_info_of_course(M[i + j], x, y + j);
		}
	}
}

void view_student_info_of_course(Data* M, int n) {
	textBgColor(0, 15);
	system("cls");
	int x = 10;
	int y = 14;
	textBgColor(4, 6);
	DrawTextFile ("_assets\\objects\\student.txt", 10, 3);
	drawRectangle(0, y - 2, 120, 13, 11);
	textBgColor(0, 11);
	printtext("NO", x, y - 1);
	printtext("ID", x + 7, y - 1);
	printtext("Name", x + 35, y - 1);
	printtext("Birthday", x + 57, y - 1);
	printtext("Sex", x + 80, y - 1);
	printtext("ID Social", x + 90, y - 1);
	char ch;
	int tab_now = 0;
	view_10_student_info_of_course(M, tab_now * 10, n, x, y);
	do {
		hidePointer();
		ch = _getch();
		if (ch == 27) {
			return;
		}
		else {
			if (ch == 72 && tab_now > 0)
			{
				tab_now--;
				drawRectangle(0, y, 120, 11, 11);
				view_10_student_info_of_course(M, tab_now * 10, n, x, y);
			}
			if (ch == 80 && tab_now < (n - 1) / 10)
			{
				tab_now++;
				drawRectangle(0, y, 120, 11, 11);
				view_10_student_info_of_course(M, tab_now * 10, n, x, y);
			}
		}
	} while (true);
}

void view_1_course_of_list_course(Course M, int x, int y) {
	printtext(M.ID_course, x, y);
	printtext(M.name, x + 8, y);//12 ki tu cho id
	printtext(M.teacher, x + 33, y);
	printtext(to_string(M.Num_of_creadit), x + 59, y);//30 ki tu cho ten
	printtext(to_string(M.Max_student), x + 75, y);//14 ki tu cho 1 diem
	printtext(M.DayOfWeek, x + 87, y);//14 ki tu cho 1 diem
	printtext(M.session[0], x + 97, y);//14 ki tu cho 1 diem
	printtext(M.session[1], x + 107, y);
}
void view_10_course_of_list_course(Course* M, int i, int n, int x, int y) {
	if (n - i >= 10) {
		for (int j = 0; j < 10; j++) {
			view_1_course_of_list_course(M[i + j], x, y + j);
		}
	}
	else {
		for (int j = 0; j < n - i; j++) {
			view_1_course_of_list_course(M[i + j], x, y + j);
		}
	}

}
int view_course_in_year(Course* M, int n, drawTxt fun) {
	if (M == NULL) {
		return -1;
	}
	textBgColor(0, 15);
	system("cls");
	int x = 1;
	int y = 14;
	fun();
	drawRectangle(0, y - 2, 120, 13, 11);
	textBgColor(0, 11);
	printtext("ID COURSE", x + 2, y - 1);
	printtext("COURSE NAME", x + 12, y - 1);//12 ki tu cho id
	printtext("TEACHER NAME", x + 35, y - 1);
	printtext("NUMBER OF CREDITS", x + 50, y - 1);//30 ki tu cho ten
	printtext("MAX STUDENT", x + 72, y - 1);
	printtext("DAY", x + 87, y - 1);//14 ki tu cho 1 diem
	printtext("SESSION 1", x + 94, y - 1);//14 ki tu cho 1 diem
	printtext("SESSION 2", x + 104, y - 1);//14 ki tu cho 1 diem
	char ch;
	int tab_now = 0;
	view_10_course_of_list_course(M, tab_now * 10, n, x, y);
	do {
		hidePointer();
		ch = _getch();
		//[ESC]
		if (ch == 27) {
			return-1;
		}
		else {
			//Control Up down 
			if (ch == 72 && tab_now > 0) //up
			{
				tab_now--;
				drawRectangle(0, y, 120, 11, 11);
				view_10_course_of_list_course(M, tab_now * 10, n, x, y);
			}
			if (ch == 80 && tab_now < (n - 1) / 10) //down
			{
				tab_now++;
				drawRectangle(0, y, 120, 11, 11);
				view_10_course_of_list_course(M, tab_now * 10, n, x, y);
			}
			if (ch == 13) {
				return tab_now;
			}
		}
	} while (true);
}