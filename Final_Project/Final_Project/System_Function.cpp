#include "System_Function.h"

void drawMenu(string* S, int n, int x, int y, int dis, drawTXT function)
{
	hidePointer();
	int maxlength = 0;
	maxlength += 1;
	function();

	drawRectangle(x - 10, y, maxlength, n + (n - 1) * dis, 11);
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			drawRectangle(x, y, maxlength - 20, 1, 0);
			textBgColor(15, 0);
			printtext(S[i], x, y + (dis + 1) * i);
		}
		else
			textBgColor(0, 15);
		printtext(S[i], x, y + (dis + 1) * i);
		textBgColor(0, 15);
	}
}

void MoveUp(int X, int& Y, int dis)
{
	Y = Y - (dis + 1);
	gotoxy(X, Y);
}

void MoveDown(int X, int& Y, int dis)
{
	Y = Y + (dis + 1);
	gotoxy(X, Y);
}

int Select(int a, string A[], int _X, int _Y, int dis)
{
	char key;
	int X = _X, Y = _Y;
	int TOP_LIMIT = _Y;
	int BOTTOM_LIMIT = _Y + (dis + 1) * (a - 1);
	int i = 0;
	while (true) {
		key = toupper(_getch());
		if (key == ESC) {
			return -1;
		}
		else {
			if (i >= 0 && i < a && Y <= 23 + a) {
				if (key == UP && Y > TOP_LIMIT) {
					drawRectangle(X, Y, 0, 1, 15);
					gotoxy(X, Y);
					textBgColor(0, 15);
					cout << A[i];
					MoveUp(X, Y, dis);
					i--;
					drawRectangle(X, Y, 0, 1, 0);
					textBgColor(15, 0);
					gotoxy(X, Y);
					cout << A[i];
					textBgColor(0, 15);
				}
				else if (key == DOWN && Y < BOTTOM_LIMIT) {
					drawRectangle(X, Y, 0, 1, 15);
					gotoxy(X, Y);
					textBgColor(0, 15);
					cout << A[i];
					MoveDown(X, Y, dis);
					i++;
					drawRectangle(X, Y, 0, 1, 0);
					textBgColor(15, 0);
					gotoxy(X, Y);
					cout << A[i];
					textBgColor(0, 15);
				}
				else if (key == ENTER) {
					return i;
				}
			}
		}
	}
}

void rewrite_course_of_student_file(User user, string fileName, string data, int command_flag) {
	fstream file_prv, file_aft;
	string oldName = fileName + ".csv";
	string newName = fileName + "new" + ".csv";
	file_prv.open(oldName, ios::in);
	file_aft.open(newName, ios::out);
	string temp;
	bool flag_change = true;
	while (file_prv.eof() == false) {
		getline(file_prv, temp);
		string temp1 = "";
		int i = 0;
		for (i = 0; i < temp.length(); i++) {
			if (temp[i] == ',' || i == temp.length() - 1)
			{
				if (i == temp.length() - 1) {
					temp1 += temp[i];
				}
				break;
			}
			else if (temp[i] != ',') {
				temp1 += temp[i];
			}
		}
		if (user.ID.compare(temp1) != 0) {
			if (flag_change == true) {
				file_aft << temp;
				flag_change = false;
			}
			else {
				file_aft << '\n' << temp;
			}
		}
		else {
			if (command_flag >= 0) {
				temp1 = temp + ',' + data;
			}
			else {
				string temp2 = "";
				for (i = i + 1; i < temp.length(); i++) {
					if (temp[i] == ',' || i == temp.length() - 1)
					{
						if (i == temp.length() - 1) {
							temp2 += temp[i];
						}
						if (_strcmpi(temp2.c_str(), data.c_str()) != 0) {
							temp1 = temp1 + ',' + temp2;
						}
						temp2 = "";
					}
					else if (temp[i] != ',') {
						temp2 += temp[i];
					}
				}
			}
			if (flag_change == true) {
				file_aft << temp1;
				flag_change = false;
			}
			else {
				file_aft << '\n' << temp1;
			}
		}
	}
	file_prv.close();
	file_aft.close();
	remove(oldName.c_str());
	rename(newName.c_str(), oldName.c_str());
}

void rewrite_course_file(User user, string fileName, int command_flag) {
	fstream file_prv, file_aft;
	string oldName = fileName + ".csv";
	string newName = fileName + "new" + ".csv";
	file_prv.open(oldName, ios::in);
	file_aft.open(newName, ios::out);
	string temp;
	bool flag_change = true;
	while (file_prv.eof() == false) {
		getline(file_prv, temp, ',');
		if (_strcmpi(temp.c_str(), user.info.IDstd.c_str()) == 0) {
			getline(file_prv, temp);
			continue;
		}
		else {
			if (flag_change == true) {
				file_aft << temp << ',';
				flag_change = false;
			}
			else {
				file_aft << '\n' << temp << ',';
			}
			getline(file_prv, temp);
			file_aft << temp;
		}
	}
	if (command_flag >= 0) {
		temp = user.info.IDstd + ',' + user.info.name + ',' + user.info.Bir + ',' + user.info.sex + ',' + user.info.IDsocial;
		if (flag_change == true) {
			file_aft << temp;
			flag_change = false;
		}
		else {
			file_aft << '\n' << temp;
		}
	}
	file_prv.close();
	file_aft.close();
	remove(oldName.c_str());
	rename(newName.c_str(), oldName.c_str());
}
int getyearData(string* data1, int* data2, string filename) {

	ifstream f;
	f.open(filename, ios::in);
	string temp;
	int i = 0;
	getline(f, temp);
	while (!f.eof()) {
		getline(f, data1[i], ',');
		getline(f, temp);
		data2[i] = atoi(temp.c_str());
		i++;
	}
	return i;
}
//void change_Year_Semester(SchoolYear& S) {
//	string* year;
//	int* semester;
//	string filename = "_assets/year-semester.csv";
//	int n = countLine(filename) - 1;
//	year = new string[n];
//	semester = new int[n];
//	getyearData(year, semester, filename);
//	system("cls");
//
//	drawMenu(year, n, 55, 15, 1, &drawASCIIchangeYear);
//	int A = MoveAndChoose(n, year, 55, 15, 1);
//	if (A == -1) {
//		return;
//	}
//	string* semester_of_year = new string[semester[A]];
//	for (int i = 0; i < semester[A]; i++) {
//		semester_of_year[i] = "Semester" + to_string(i + 1);
//	}
//	system("cls");
//
//	drawMenu(semester_of_year, semester[A], 55, 15, 1, &drawASCIIchangeSemester);
//	int i = MoveAndChoose(semester[A], semester_of_year, 55, 15, 1);
//	if (i == -1) {
//		return;
//	}
//	S.year = year[A];
//	S.semester.Name = semester_of_year[i];
//}
//void DisPlay_Course_Of_Student(SchoolYear Y, User A) {
//	char ch;
//	hidePointer();
//	get_course(A, Y);
//	read_course(A, Y);
//	do {
//		drawRectangle(27, 29, 60, 1, 10);
//		textColor(496);
//		string text = Y.semester.Name + "; Year: " + Y.year + ".   Press[C] to change!";
//		printtext(text, 32, 29);
//		ch = getch();
//		//[ESC]
//		if (ch == 27) {
//			return;
//		}
//		else {
//			//Control Up down 
//			if (ch == 'c' || ch == 'C') //up
//			{
//				change_Year_Semester(Y);
//				int a = get_course(A, Y);
//				if (a == -1) {
//					drawRectangle(3, 14, 115, 3, 4);
//					printtext("Invalid school year ", 50, 15);
//					textBgColor(0, 15);
//					Sleep(1800);
//					determineYearSemesterNow(Y.year, Y.semester.Name);
//				}
//				read_course(A, Y);
//			}
//		}
//	} while (true);
//}
void edit_score(User& A, SchoolYear SY, Mark* M) {
	//char ch;
	//int line_now = 1;
	//int x = 15, y = 14;
	//int line = 0;
	//MarkNode* temp = A.info.phead;
	//while (temp != NULL) {
	//	line++;
	//	temp = temp->pNext;
	//}
	//if (M == NULL) {
	//	drawRectangle(0, 17, 120, 3, 6);
	//	printtext("He/she has not registered for any courses this semester ", 30, 18);
	//	Sleep(2700);
	//	textBgColor(0, 15);
	//	return;
	//}
	//drawRectangle(1, y + line_now, 115, 1, 14);
	//textBgColor(0, 14);
	//view_1_line(M[line_now - 1], x, y + line_now);
	//do {
	//	hidePointer();
	//	ch = _getch();
	//	//[ESC]
	//	if (ch == 27) {
	//		drawRectangle(1, y + line_now, 115, 1, 11);
	//		textBgColor(0, 11);
	//		view_1_line(M[line_now - 1], x, y + line_now);
	//		break;
	//	}
	//	else {
	//		//Control Up down 
	//		if (ch == 72 && line_now > 1) //up
	//		{
	//			drawRectangle(1, y + line_now, 115, 1, 11);
	//			textBgColor(0, 11);
	//			view_1_line(M[line_now - 1], x, y + line_now);

	//			line_now--;
	//			drawRectangle(1, y + line_now, 115, 1, 14);
	//			textBgColor(0, 14);
	//			view_1_line(M[line_now - 1], x, y + line_now);
	//		}
	//		if (ch == 80 && line_now < line) //down
	//		{
	//			drawRectangle(1, y + line_now, 115, 1, 11);
	//			textBgColor(0, 11);
	//			view_1_line(M[line_now - 1], x, y + line_now);

	//			line_now++;
	//			drawRectangle(1, y + line_now, 115, 1, 14);
	//			textBgColor(0, 14);
	//			view_1_line(M[line_now - 1], x, y + line_now);
	//		}
	//		if (ch == 13) {
	//			string fCheck = "_assets/SchoolYear/" + SY.year + '/' + SY.semester.Name + "/Course/score/" + M[line_now - 1].ID + csv_tail;
	//			fstream fcheck;
	//			fcheck.open(fCheck, ios::in);
	//			if (!fcheck.good())
	//			{
	//				gotoxy(x + 42, y + line_now);
	//				cout << "Fail!! This subject has not been graded by the teacher yet.";
	//				Sleep(900);
	//				drawRectangle(1, y + line_now, 115, 1, 14);
	//				textBgColor(0, 14);
	//				view_1_line(M[line_now - 1], x, y + line_now);
	//				fcheck.close();
	//				continue;
	//			}
	//			else {
	//				fcheck.close();
	//				int y_now = y + line_now;
	//				int x_now = x + 42, x_max = x + 70, x_min = x + 42;
	//				string S[] = { to_string(M[line_now - 1].Midterm_Mark),to_string(M[line_now - 1].Final_Mark),to_string(M[line_now - 1].Other_Mark) };
	//				drawRectangle(x + 42, y_now, 14, 1, 15);
	//				textBgColor(0, 15);
	//				printtext(to_string(M[line_now - 1].Midterm_Mark), x + 42, y_now);
	//				char CH;
	//				do
	//				{
	//					CH = _getch();
	//					//ESC
	//					if (CH == 27) {
	//						drawRectangle(x_now, y_now, 14, 1, 14);
	//						textBgColor(0, 14);
	//						printtext(S[(x_now - x_min) / 14], x_now, y_now);
	//						break;
	//					}
	//					else {
	//						//Left 
	//						if (CH == 75 && x_now > x_min) {
	//							drawRectangle(x_now, y_now, 14, 1, 14);
	//							textBgColor(0, 14);
	//							printtext(S[(x_now - x_min) / 14], x_now, y_now);

	//							x_now = x_now - 14;
	//							drawRectangle(x_now, y_now, 14, 1, 15);
	//							textBgColor(0, 15);
	//							printtext(S[(x_now - x_min) / 14], x_now, y_now);
	//						}
	//						//Right
	//						if (CH == 77 && x_now < x_max) {
	//							drawRectangle(x_now, y_now, 14, 1, 14);
	//							textBgColor(0, 14);
	//							printtext(S[(x_now - x_min) / 14], x_now, y_now);

	//							x_now = x_now + 14;
	//							drawRectangle(x_now, y_now, 14, 1, 15);
	//							textBgColor(0, 15);
	//							printtext(S[(x_now - x_min) / 14], x_now, y_now);
	//						}

	//						//[ENTER]
	//						if (CH == 13) {
	//							drawRectangle(x_now, y_now, 14, 1, 15);
	//							textBgColor(0, 15);
	//							float i;
	//							string mark;
	//							int flag = 0;
	//							do {
	//								mark = "";
	//								gotoxy(x_now, y_now);
	//								insertMark(mark, 5, flag);
	//								if (flag == -1) {
	//									drawRectangle(x_now, y_now, 14, 1, 15);
	//									textBgColor(0, 15);
	//									printtext(S[(x_now - x_min) / 14], x_now, y_now);
	//									break;
	//								}
	//								else {
	//									i = atof(mark.c_str());
	//									if (i > 10) {
	//										gotoxy(x_now, y_now);
	//										cout << "Erroll!!";
	//										Sleep(900);
	//										drawRectangle(x_now, y_now, 14, 1, 15);
	//									}
	//								}
	//							} while (i > 10);
	//							if (flag == 0) {
	//								int a = (x_now - x_min) / 14;
	//								switch (a)
	//								{
	//								case 0:
	//									M[line_now - 1].Midterm_Mark = i;
	//									S[(x_now - x_min) / 14] = to_string(M[line_now - 1].Midterm_Mark);
	//									break;
	//								case 1:
	//									M[line_now - 1].Final_Mark = i;
	//									S[(x_now - x_min) / 14] = to_string(M[line_now - 1].Final_Mark);
	//									break;
	//								case 2:
	//									M[line_now - 1].Other_Mark = i;
	//									S[(x_now - x_min) / 14] = to_string(M[line_now - 1].Other_Mark);
	//									break;
	//								default:
	//									break;
	//								}
	//								M[line_now - 1].Total_Mark = 0.3 * M[line_now - 1].Midterm_Mark + 0.6 * M[line_now - 1].Final_Mark + 0.1 * M[line_now - 1].Other_Mark;
	//								drawRectangle(1, y + line_now, 115, 1, 14);
	//								textBgColor(0, 14);
	//								view_1_line(M[line_now - 1], x, y + line_now);
	//								drawRectangle(x_now, y_now, 14, 1, 15);
	//								textBgColor(0, 15);
	//								printtext(S[(x_now - x_min) / 14], x_now, y_now);
	//								save_Mark(A, M, line_now - 1, SY);
	//							}
	//						}

	//					}
	//				} while (true);
	//			}

	//		}
	//	}
	//} while (true);
	//textBgColor(0, 15);
}
void DisPlay_Mark_Of_Student(SchoolYear Y, User A) {
	//char ch;
	//int a = get_course(A, Y);
	//view_all_score_of_1_student(A, Y);
	//do {
	//	hidePointer();
	//	drawRectangle(27, 29, 60, 1, 6);
	//	textColor(499);
	//	string text = Y.semester.Name + "; Year: " + Y.year + ".   Press[C] to change!";
	//	printtext(text, 32, 29);
	//	ch = getch();
	//	//[ESC]
	//	if (ch == 27) {
	//		return;
	//	}
	//	else {
	//		if (ch == 'c' || ch == 'C')
	//		{
	//			change_Year_Semester(Y);
	//			int a = get_course(A, Y);
	//			if (a == -1) {
	//				drawRectangle(3, 14, 115, 3, 4);
	//				printtext("Invalid school year ", 50, 15);
	//				textBgColor(0, 15);
	//				Sleep(1800);
	//				determineYearSemesterNow(Y.year, Y.semester.Name);
	//			}
	//			view_all_score_of_1_student(A, Y);
	//		}
	//	}
	//} while (true);
	//textBgColor(0, 15);
}

void edit_score_in_list_course(User& A, SchoolYear SY, string IDcourse) {
	//int n = 0;
	//Mark* M = read_file_score_of_course(SY, IDcourse, n);
	//if (M == NULL) {
	//	//thong báo mở file thất bại
	//	textBgColor(0, 15);
	//	system("cls");
	//	drawRectangle(3, 14, 115, 3, 4);
	//	printtext("Fail!! The teacher has not entered the score for this course!! ", 35, 15);
	//	textBgColor(0, 15);
	//	Sleep(1800);
	//	return;
	//}
	//char ch;
	//int line_now = 0;
	//int x = 10, y = 14;
	//int tab_now = view_score_of_course_in_year(M, n);
	//if (tab_now == -1) {
	//	textBgColor(0, 15);
	//	return;
	//}
	//drawRectangle(1, y + line_now, 115, 1, 14);
	//textBgColor(0, 14);
	//view_1_score_of_course(M[tab_now * 10], x, y);
	//int count = tab_now * 10;
	//do {
	//	if (tab_now == -1) {
	//		textBgColor(0, 15);
	//		return;
	//	}
	//	hidePointer();
	//	ch = _getch();
	//	//[ESC]
	//	if (ch == 27) {
	//		tab_now = view_score_of_course_in_year(M, n);
	//		if (tab_now == -1) {
	//			textBgColor(0, 15);
	//			return;
	//		}
	//		line_now = 0;
	//		count = tab_now * 10;
	//		drawRectangle(1, y + line_now, 115, 1, 14);
	//		textBgColor(0, 14);
	//		view_1_score_of_course(M[tab_now * 10], x, y);
	//	}
	//	else {
	//		//Control Up down 
	//		if (ch == 72 && line_now > 0) //up
	//		{
	//			drawRectangle(1, y + line_now, 115, 1, 11);
	//			textBgColor(0, 11);
	//			view_1_score_of_course(M[count], x, y + line_now);

	//			line_now--;
	//			count--;
	//			drawRectangle(1, y + line_now, 115, 1, 14);
	//			textBgColor(0, 14);
	//			view_1_score_of_course(M[count], x, y + line_now);
	//		}
	//		else if (ch == 72 && line_now == 0 && count > 0) {
	//			count--;
	//			drawRectangle(0, y, 120, 11, 11);
	//			view_10_score_of_course(M, count, n, x, y);
	//			drawRectangle(1, y + line_now, 115, 1, 14);
	//			textBgColor(0, 14);
	//			view_1_score_of_course(M[count], x, y + line_now);
	//		}
	//		else if (ch == 80 && line_now < 9 && count < n - 1) //down
	//		{
	//			drawRectangle(1, y + line_now, 115, 1, 11);
	//			textBgColor(0, 11);
	//			view_1_score_of_course(M[count], x, y + line_now);

	//			line_now++;
	//			count++;
	//			drawRectangle(1, y + line_now, 115, 1, 14);
	//			textBgColor(0, 14);
	//			view_1_score_of_course(M[count], x, y + line_now);
	//		}
	//		else if (ch == 80 && line_now == 9 && count < n - 1) {
	//			count++;
	//			drawRectangle(0, y, 120, 11, 11);
	//			view_10_score_of_course(M, count - 9, n, x, y);
	//			drawRectangle(1, y + line_now, 115, 1, 14);
	//			textBgColor(0, 14);
	//			view_1_score_of_course(M[count], x, y + line_now);
	//		}
	//		if (ch == 13) {
	//			int y_now = y + line_now;
	//			int x_now = x + 52, x_max = x + 80, x_min = x + 52;
	//			string S[] = { to_string(M[count].Midterm_Mark),to_string(M[count].Final_Mark),to_string(M[count].Other_Mark) };
	//			drawRectangle(x_now, y_now, 14, 1, 15);
	//			textBgColor(0, 15);
	//			printtext(to_string(M[count].Midterm_Mark), x_now, y_now);
	//			char CH;
	//			do
	//			{
	//				CH = _getch();
	//				//ESC
	//				if (CH == 27) {
	//					drawRectangle(x_now, y_now, 14, 1, 14);
	//					textBgColor(0, 14);
	//					printtext(S[(x_now - x_min) / 14], x_now, y_now);
	//					break;
	//				}
	//				else {
	//					//Left 
	//					if (CH == 75 && x_now > x_min) {
	//						drawRectangle(x_now, y_now, 14, 1, 14);
	//						textBgColor(0, 14);
	//						printtext(S[(x_now - x_min) / 14], x_now, y_now);
	//						x_now = x_now - 14;
	//						drawRectangle(x_now, y_now, 14, 1, 15);
	//						textBgColor(0, 15);
	//						printtext(S[(x_now - x_min) / 14], x_now, y_now);
	//					}
	//					//Right
	//					if (CH == 77 && x_now < x_max) {
	//						drawRectangle(x_now, y_now, 14, 1, 14);
	//						textBgColor(0, 14);
	//						printtext(S[(x_now - x_min) / 14], x_now, y_now);
	//						x_now = x_now + 14;
	//						drawRectangle(x_now, y_now, 14, 1, 15);
	//						textBgColor(0, 15);
	//						printtext(S[(x_now - x_min) / 14], x_now, y_now);
	//					}
	//					//[ENTER]
	//					if (CH == 13) {
	//						drawRectangle(x_now, y_now, 14, 1, 15);
	//						textBgColor(0, 15);
	//						float i;
	//						string mark;
	//						int flag = 0;
	//						do {
	//							mark = "";
	//							gotoxy(x_now, y_now);
	//							insertMark(mark, 5, flag);
	//							if (flag == -1) {
	//								drawRectangle(x_now, y_now, 14, 1, 15);
	//								textBgColor(0, 15);
	//								printtext(S[(x_now - x_min) / 14], x_now, y_now);
	//								break;
	//							}
	//							else {
	//								i = atof(mark.c_str());
	//								if (i > 10) {
	//									gotoxy(x_now, y_now);
	//									cout << "Erroll!!";
	//									Sleep(900);
	//									drawRectangle(x_now, y_now, 14, 1, 15);
	//								}
	//							}
	//						} while (i > 10);
	//						if (flag == 0) {
	//							int a = (x_now - x_min) / 14;
	//							switch (a)
	//							{
	//							case 0:
	//								M[count].Midterm_Mark = i;
	//								S[(x_now - x_min) / 14] = to_string(M[count].Midterm_Mark);
	//								break;
	//							case 1:
	//								M[count].Final_Mark = i;
	//								S[(x_now - x_min) / 14] = to_string(M[count].Final_Mark);
	//								break;
	//							case 2:
	//								M[count].Other_Mark = i;
	//								S[(x_now - x_min) / 14] = to_string(M[count].Other_Mark);
	//								break;
	//							default:
	//								break;
	//							}
	//							M[count].Total_Mark = 0.3 * M[count].Midterm_Mark + 0.6 * M[count].Final_Mark + 0.1 * M[count].Other_Mark;
	//							drawRectangle(1, y + line_now, 115, 1, 14);
	//							textBgColor(0, 14);
	//							view_1_score_of_course(M[count], x, y + line_now);
	//							drawRectangle(x_now, y_now, 14, 1, 15);
	//							textBgColor(0, 15);
	//							printtext(S[(x_now - x_min) / 14], x_now, y_now);
	//							save_Mark_With_List_Cousre(IDcourse, M[count], SY);
	//						}
	//					}
	//				}

	//			} while (true);


	//		}
	//	}
	//} while (true);
	//textBgColor(0, 15);
}
void enroll_course(User& A, SchoolYear s_y) {
	//string semester_path = "_assets/SchoolYear/" + s_y.year + '/' + s_y.semester.Name + '/';
	//string class_path = semester_path + "Class/";
	//string course_path = semester_path + "Course/";
	////hàm trang trí
	////hàm hiện danh sách các môn học.

	//Course* course_input = select_course(A, s_y, &read_file_List_course, &drawASCIIenrolCourse);
	//if (course_input == NULL) {
	//	return;
	//}
	////kiểm tra xem trong danh sách môn học của sinh viên đã có môn này hay chưa
	//get_all_course(A, s_y);
	//MarkNode* Mtemp = A.info.phead;
	//while (Mtemp != NULL) {
	//	if (_strcmpi(course_input->ID_course.c_str(), Mtemp->data.ID.c_str()) == 0) {
	//		//nếu có thì return.
	//		drawASCIIfailEnrol();
	//		Sleep(1800);
	//		return;
	//	}
	//	Mtemp = Mtemp->pNext;
	//}
	////chưa có thì thêm vào danh sách.
	//add_Tail_List_Mark(A.info.phead, course_input->ID_course, course_input->name, to_string(course_input->Num_of_creadit));
	////ghi them vao file;
	//string file_cousre_of_class = class_path + A.info.Class;
	//rewrite_course_of_student_file(A, file_cousre_of_class, course_input->ID_course, 1);
	//string file_cousre = course_path + course_input->ID_course;
	//rewrite_course_file(A, file_cousre, 1);
	//drawASCIIsuccessful();
	//Sleep(3000);
}
void delete_course(User& A, SchoolYear s_y) {
	//string semester_path = "_assets/SchoolYear/" + s_y.year + '/' + s_y.semester.Name + '/';
	//string class_path = semester_path + "Class/";
	//string course_path = semester_path + "Course/";
	////hàm trang trí
	////hàm hiện danh sách các môn học.
	//Course* course_input = select_course(A, s_y, &get_course_of_student, &drawASCIIdeleteCourse);
	//if (course_input == NULL) {
	//	return;
	//}
	//delete_Mark_node(A.info.phead, course_input->ID_course);
	//string file_cousre_of_class = class_path + A.info.Class;
	//rewrite_course_of_student_file(A, file_cousre_of_class, course_input->ID_course, -1);
	//string file_cousre = course_path + course_input->ID_course;
	//rewrite_course_file(A, file_cousre, -1);
	//drawASCIIsuccessful();
	//Sleep(3000);
	//return;
}
void viewStudentInCourse(User user, SchoolYear SY) {
	/*try {
		while (true) {
			User A;
			Course* SLC = select_course(A, SY, &read_file_List_course, &drawASCIIlistCourse);
			if (SLC == NULL) {
				return;
			}
			int n = 0;
			Data* M = read_file_student_info_of_course(SY, SLC->ID_course, n);
			view_student_info_of_course(M, n);
		}
	}
	catch (const char* err) {
		drawRectangle(3, 14, 115, 3, 4);
		printtext(err, 50, 15);
		textBgColor(0, 15);
		Sleep(1800);
	}*/
}
void Output_info(User A) {
	system("cls");
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
	printtext(M.Name, x + 12, y);//12 ki tu cho id
	printtext(to_string(M.Midterm_Mark), x + 42, y);//30 ki tu cho ten
	printtext(to_string(M.Final_Mark), x + 56, y);//14 ki tu cho 1 diem
	printtext(to_string(M.Other_Mark), x + 70, y);//14 ki tu cho 1 diem
	printtext(to_string(M.Total_Mark), x + 84, y);//14 ki tu cho 1 diem
}
Mark* view_all_score_of_1_student(User A, SchoolYear Y) {
	system("cls");
	int n;
	get_score(A, Y, n);

	int x = 15;
	int y = 14;
	textBgColor(4, 6);
	drawRectangle(0, 13, 120, n + 3, 11);
	textBgColor(0, 11);
	printtext("ID", x, y);
	printtext("Name of Course", x + 12, y);//12 ki tu cho id
	printtext("Midterm Mark", x + 42, y);//30 ki tu cho ten
	printtext("Final Mark", x + 56, y);//14 ki tu cho 1 diem
	printtext("Other Mark", x + 70, y);//14 ki tu cho 1 diem
	printtext("Total Mark", x + 84, y);//14 ki tu cho 1 diem
	y++;
	if (n == 0) {
		drawRectangle(0, 17, 120, 3, 6);
		printtext("You has not registered for any courses this semester ", 30, 18);
		textBgColor(0, 15);
		return NULL;
	}
	Mark* M = new Mark[n];
	MarkNode* temp = A.info.phead;
	for (int i = 0; i < n; i++) {
		M[i] = temp->data;
		view_1_line(M[i], x, y + i);
		temp = temp->pNext;
	}
	textBgColor(0, 15);
	return M;
}
void view_1_score_of_course(Mark M, int x, int y) {
	printtext(M.ID, x, y);
	printtext(M.Name, x + 12, y);//12 ki tu cho id
	printtext(M.C, x + 42, y);
	printtext(to_string(M.Midterm_Mark), x + 52, y);//30 ki tu cho ten
	printtext(to_string(M.Final_Mark), x + 66, y);//14 ki tu cho 1 diem
	printtext(to_string(M.Other_Mark), x + 80, y);//14 ki tu cho 1 diem
	printtext(to_string(M.Total_Mark), x + 94, y);//14 ki tu cho 1 diem
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
	textBgColor(0, 11);
	printtext("ID", x, y - 1);
	printtext("Name", x + 12, y - 1);//12 ki tu cho id
	printtext("Class", x + 42, y - 1);
	printtext("Midterm Mark", x + 52, y - 1);//30 ki tu cho ten
	printtext("Final Mark", x + 66, y - 1);//14 ki tu cho 1 diem
	printtext("Other Mark", x + 80, y - 1);//14 ki tu cho 1 diem
	printtext("Total Mark", x + 94, y - 1);//14 ki tu cho 1 diem
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
int view_course_in_year(Course* M, int n, drawTXT fun) {
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
Course* select_course(User A, SchoolYear SY, func_Get_course fun, drawTXT fundraw) {
	int n = 0;
	Course* M = fun(A, SY, n);
	if (M == NULL) {
		throw "There isn't course.";
	}
	char ch;
	int line_now = 0;
	int x = 1, y = 14;
	int tab_now = view_course_in_year(M, n, fundraw);
	if (tab_now == -1) {
		textBgColor(0, 15);
		return NULL;
	}
	drawRectangle(1, y + line_now, 115, 1, 14);
	textBgColor(0, 14);
	view_1_course_of_list_course(M[tab_now * 10], x, y);
	int count = tab_now * 10;
	do {
		if (tab_now == -1) {
			textBgColor(0, 15);
			return NULL;
		}
		hidePointer();
		ch = _getch();
		//[ESC]
		if (ch == 27) {
			tab_now = view_course_in_year(M, n, fundraw);
			if (tab_now == -1) {
				textBgColor(0, 15);
				return NULL;
			}
			line_now = 0;
			count = tab_now * 10;
			drawRectangle(1, y + line_now, 115, 1, 14);
			textBgColor(0, 14);
			view_1_course_of_list_course(M[tab_now * 10], x, y);
		}
		else {
			//Control Up down 
			if (ch == 72 && line_now > 0) //up
			{
				drawRectangle(1, y + line_now, 115, 1, 11);
				textBgColor(0, 11);
				view_1_course_of_list_course(M[count], x, y + line_now);

				line_now--;
				count--;
				drawRectangle(1, y + line_now, 115, 1, 14);
				textBgColor(0, 14);
				view_1_course_of_list_course(M[count], x, y + line_now);
			}
			else if (ch == 72 && line_now == 0 && count > 0) {
				count--;
				drawRectangle(0, y, 120, 11, 11);
				view_10_course_of_list_course(M, count, n, x, y);
				drawRectangle(1, y + line_now, 115, 1, 14);
				textBgColor(0, 14);
				view_1_course_of_list_course(M[count], x, y + line_now);
			}
			else if (ch == 80 && line_now < 9 && count < n - 1) //down
			{
				drawRectangle(1, y + line_now, 115, 1, 11);
				textBgColor(0, 11);
				view_1_course_of_list_course(M[count], x, y + line_now);

				line_now++;
				count++;
				drawRectangle(1, y + line_now, 115, 1, 14);
				textBgColor(0, 14);
				view_1_course_of_list_course(M[count], x, y + line_now);
			}
			else if (ch == 80 && line_now == 9 && count < n - 1) {
				count++;
				drawRectangle(0, y, 120, 11, 11);
				view_10_course_of_list_course(M, count - 9, n, x, y);
				drawRectangle(1, y + line_now, 115, 1, 14);
				textBgColor(0, 14);
				view_1_course_of_list_course(M[count], x, y + line_now);
			}
			if (ch == 13) {
				return &M[count];
			}
		}
	} while (true);
	textBgColor(0, 15);
}
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
	drawRectangle(0, y - 2, 120, 13, 11);
	textBgColor(0, 11);
	printtext("NO", x, y - 1);
	printtext("ID", x + 7, y - 1);//12 ki tu cho id
	printtext("Name", x + 35, y - 1);
	printtext("Birthday", x + 57, y - 1);//30 ki tu cho ten
	printtext("Sex", x + 80, y - 1);//14 ki tu cho 1 diem
	printtext("ID Social", x + 90, y - 1);//14 ki tu cho 1 diem
	char ch;
	int tab_now = 0;
	view_10_student_info_of_course(M, tab_now * 10, n, x, y);
	do {
		hidePointer();
		ch = _getch();
		//[ESC]
		if (ch == 27) {
			return;
		}
		else {
			//Control Up down 
			if (ch == 72 && tab_now > 0) //up
			{
				tab_now--;
				drawRectangle(0, y, 120, 11, 11);
				view_10_student_info_of_course(M, tab_now * 10, n, x, y);
			}
			if (ch == 80 && tab_now < (n - 1) / 10) //down
			{
				tab_now++;
				drawRectangle(0, y, 120, 11, 11);
				view_10_student_info_of_course(M, tab_now * 10, n, x, y);
			}
		}
	} while (true);
}
