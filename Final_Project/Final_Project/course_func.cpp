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

void change_Year_Semester(SchoolYear& S) {
	/*string* year;
	int* semester;
	string filename = "file_save/year-semester.csv";
	int n = countLine(filename) - 1;
	year = new string[n];
	semester = new int[n];
	getyearData(year, semester, filename);
	system("cls");

	drawMenu(year, n, 55, 15, 1, &drawASCIIchangeYear);
	int A = Select(n, year, 55, 15, 1);
	if (A == -1) {
		return;
	}
	string* semester_of_year = new string[semester[A]];
	for (int i = 0; i < semester[A]; i++) {
		semester_of_year[i] = "Semester" + to_string(i + 1);
	}
	system("cls");

	drawMenu(semester_of_year, semester[A], 55, 15, 1, &drawASCIIchangeSemester);
	int i = Select(semester[A], semester_of_year, 55, 15, 1);
	if (i == -1) {
		return;
	}
	S.year = year[A];
	S.semester.Name = semester_of_year[i];*/
}
void DisPlay_Course_Of_Student(SchoolYear Y, User A) {
	char ch;
	//int a = get_course(A, Y);
	view_all_score_of_1_student(A, Y);
	do {
		hidePointer();
		drawRectangle(27, 29, 60, 1, 6);
		textColor(499);
		string text = Y.semester.Name + "; Year: " + Y.year + ".   Press[C] to change!";
		printtext(text, 32, 29);
		ch = getch();
		//[ESC]
		if (ch == 27) {
			return;
		}
		else {
			if (ch == 'c' || ch == 'C')
			{
				change_Year_Semester(Y);
				int a = get_course(A, Y);
				if (a == -1) {
					drawRectangle(3, 14, 115, 3, 4);
					printtext("Invalid school year ", 50, 15);
					textBgColor(0, 15);
					Sleep(1800);
					determineYearSemesterNow(Y.year, Y.semester.Name);
				}
				view_all_score_of_1_student(A, Y);
			}
		}
	} while (true);
	textBgColor(0, 15);
}
void edit_score(User& A, SchoolYear SY, Mark* M);
void DisPlay_Mark_Of_Student(SchoolYear Y, User A) {

}
void edit_score_in_list_course(User& A, SchoolYear SY, string IDcourse) {

}
//void delete_course(User& A, SchoolYear s_y) {
//	string semester_path = "_assets/SchoolYear/" + s_y.year + '/' + s_y.semester.Name + '/';
//	string class_path = semester_path + "Class/";
//	string course_path = semester_path + "Course/";
//
//	Course* course_input = select_course(A, s_y, &get_course_of_student, &drawASCIIdeleteCourse);
//	if (course_input == NULL) {
//		return;
//	}
//	delete_Mark_node(A.info.phead, course_input->ID_course);
//	string file_cousre_of_class = class_path + A.info.Class;
//	rewrite_course_of_student_file(A, file_cousre_of_class, course_input->ID_course, -1);
//	string file_cousre = course_path + course_input->ID_course;
//	rewrite_course_file(A, file_cousre, -1);
//	Sleep(3000);
//	return;
//}

void viewStudentInCourse(User user, SchoolYear SY) {
	try {
		while (true) {
			/*User A;
			Course* SLC = select_course(A, SY, &read_file_List_course, &drawASCIIlistCourse);
			if (SLC == NULL) {
				return;
			}
			int n = 0;
			Data* M = read_file_student_info_of_course(SY, SLC->ID_course, n);
			view_student_info_of_course(M, n);*/
		}
	}
	catch (const char* err) {
		drawRectangle(3, 14, 115, 3, 4);
		printtext(err, 50, 15);
		textBgColor(0, 15);
		Sleep(1800);
	}
}

void Output_info(User A) {
	int a = 0;
	if (A.role == 1) {
		drawRectangle(30, 12, 50, 16, 11);
		printtext("Ma so sinh vien: " + A.info.IDstd, 35, 15);
		printtext("Lop: " + A.info.Class, 35, 17);
		a = 2;
		printtext("Chuc vu: Hoc sinh", 35, 21 + a);
	}
	else {
		drawRectangle(30, 12, 50, 13, 11);
		printtext("Email : " + A.info.IDstd + "@hcmus.edu.vn", 35, 15);
		printtext("Chuc vu: Admin", 35, 21 + a);
	}
	printtext("Ho va ten: " + A.info.name, 35, 13);
	printtext("Ngay sinh: " + A.info.Bir, 35, 17 + a);
	printtext("Gioi tinh: " + A.info.sex, 35, 19 + a);

	printtext("CMND/CCCD: " + A.info.IDsocial, 35, 23 + a);
	textBgColor(0, 15);
	system("pause");
}

void view_1_line(Mark M, int x, int y) {
	printtext(M.ID, x, y);
	printtext(M.Name, x + 12, y);
	printtext(to_string(M.Midterm_Mark), x + 42, y);
	printtext(to_string(M.Final_Mark), x + 56, y);
	printtext(to_string(M.Other_Mark), x + 70, y);
	printtext(to_string(M.Total_Mark), x + 84, y);
}

void view_1_score_of_course(Mark M, int x, int y) {
	printtext(M.ID, x, y);
	printtext(M.Name, x + 12, y);
	printtext(M.C, x + 42, y);
	printtext(to_string(M.Midterm_Mark), x + 52, y);
	printtext(to_string(M.Final_Mark), x + 66, y);
	printtext(to_string(M.Other_Mark), x + 80, y);
	printtext(to_string(M.Total_Mark), x + 94, y);
}
void view_10_score_of_course(Mark* M, int i, int n, int x, int y) {
	if (n - i >= 10) {
		for (int j = 0; j < 10; j++) {
			view_1_score_of_course(M[i + j], x, y + j);
		}
	}
	else {
		for (int j = 0; j < n - i; j++) {
			view_1_score_of_course(M[i + j], x, y + j);
		}
	}
}

int view_score_of_course_in_year(Mark* M, int n) {
	textBgColor(0, 15);
	system("cls");
	int x = 10;
	int y = 14;
	textBgColor(4, 6);
	drawRectangle(0, y - 2, 120, 13, 11);
	textBgColor(0, 11);
	printtext("ID", x, y - 1);
	printtext("Name", x + 12, y - 1);
	printtext("Class", x + 42, y - 1);
	printtext("Midterm Mark", x + 52, y - 1);
	printtext("Final Mark", x + 66, y - 1);
	printtext("Other Mark", x + 80, y - 1);
	printtext("Total Mark", x + 94, y - 1);
	char ch;
	int tab_now = 0;
	view_10_score_of_course(M, tab_now * 10, n, x, y);
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
				view_10_score_of_course(M, tab_now * 10, n, x, y);
			}
			if (ch == 80 && tab_now < (n - 1) / 10) //down
			{
				tab_now++;
				drawRectangle(0, y, 120, 11, 11);
				view_10_score_of_course(M, tab_now * 10, n, x, y);
			}
			if (ch == 13) {
				return tab_now;
			}
		}
	} while (true);
}