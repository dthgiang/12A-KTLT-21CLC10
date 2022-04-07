#include "Read_Data.h"

Course* read_file_List_course(User A, SchoolYear SY, int& n) {
	string fileName = "file_save/SchoolYear/" + SY.year + '/' + SY.semester.Name + "/course_info" + csv_tail;
	ifstream f;
	f.open(fileName, ios::in);
	if (!f.good()) {
		drawRectangle(3, 14, 115, 3, 4);
		printtext("Can't open information file.", 47, 15);
		textBgColor(0, 15);
		Sleep(1800);
		return NULL;
	}
	n = countLine(fileName) - 1;
	if (n == 0) {
		return NULL;
	}
	Course* M = new Course[n];
	string temp;
	getline(f, temp);
	for (int i = 0; i < n; i++) {
		getline(f, M[i].ID_course, ',');
		getline(f, M[i].name, ',');
		getline(f, M[i].teacher, ',');
		getline(f, temp, ',');
		M[i].Num_of_creadit = atoi(temp.c_str());
		getline(f, temp, ',');
		M[i].Max_student = atoi(temp.c_str());
		getline(f, M[i].DayOfWeek, ',');
		getline(f, M[i].session[0], ',');
		getline(f, M[i].session[1]);
	}
	f.close();
	return M;
}

void read_1_info(User& A, ifstream& f) {
	string NO_temp;
	std::getline(f, NO_temp, ',');
	A.info.NO_inclass = stoi(NO_temp);
	std::getline(f, A.info.IDstd, ',');// giáo viên thì sẽ là id đăng nhập
	getline(f, A.info.name, ',');
	getline(f, A.info.Bir, ',');
	getline(f, A.info.sex, ',');
	getline(f, A.info.IDsocial);
	A.info.phead = NULL;
}

void read_info(User& A, SchoolYear SY) {
	string year_path = "file_save/SchoolYear/" + SY.year + '/';
	string fileName;
	if (A.role == 1) {
		fileName = year_path + A.info.Class + csv_tail;
	}
	else {
		fileName = year_path + "staff.csv";
	}
	ifstream info_file;
	info_file.open(fileName, ios::in);
	string temp;
	getline(info_file, temp);
	while (info_file.eof() == false) {
		read_1_info(A, info_file);
		if (A.ID.compare(A.info.IDstd) == 0) {
			break;
		}
		else {
			continue;
		}
	}
	info_file.close();
}

void read_course(User A, SchoolYear y)
{
	system("cls");
	textBgColor(4, 10);
	DrawTextFile("_assets\\your_course.txt", 20, 4);
	drawRectangle(1, 14, 115, 2, 6);
	gotoxy(1, 15); std::cout << "N.o";
	gotoxy(8, 15); std::cout << "Id course";
	gotoxy(19, 15); std::cout << "Course name";
	gotoxy(45, 15); std::cout << "Lecturer";
	gotoxy(70, 15); std::cout << "Number of credits";
	gotoxy(90, 15); std::cout << "Max student";
	gotoxy(102, 15); std::cout << "Schedule";
	ifstream fi;
	string fileName = "database/SchoolYear/" + y.year + "/" + y.semester.Name + "/course_info.csv";
	MarkNode* tempo = new MarkNode;
	tempo = A.info.phead;
	int i = 1;
	if (tempo == NULL) {
		drawRectangle(1, 17, 115, 3, 2);
		printtext("You has not registered for any courses this semester ", 30, 18);
		textBgColor(0, 15);
		return;
	}
	while (tempo != NULL)
	{
		string fl;
		Course co;
		fi.open(fileName, ios::in);
		getline(fi, fl);
		while (!fi.eof())
		{
			read1CourseInfor(co, fi);
			if (_strcmpi(co.ID_course.c_str(), tempo->data.ID.c_str()) == 0)
			{
				drawRectangle(1, 15 + i, 115, 2, 6);
				gotoxy(1, 15 + i); std::cout << i;
				gotoxy(8, 15 + i); std::cout << co.ID_course;
				gotoxy(19, 15 + i); std::cout << co.name;
				gotoxy(45, 15 + i); std::cout << co.teacher;
				gotoxy(78, 15 + i); std::cout << co.Num_of_creadit;
				gotoxy(94, 15 + i); std::cout << co.Max_student;
				gotoxy(102, 15 + i); std::cout << co.Schedule;
				i++;
				tempo = tempo->pNext;
				break;
			}
		}
		fi.close();
		textBgColor(0, 15);
	}
}
void read1CourseInfor(Course& A, ifstream& f)
{
	string flag;
	getline(f, A.ID_course, ',');
	getline(f, A.name, ',');
	getline(f, A.teacher, ',');
	getline(f, flag, ',');
	A.Num_of_creadit = stoi(flag, 0, 10);
	getline(f, flag, ',');
	A.Max_student = stoi(flag, 0, 10);
	getline(f, A.DayOfWeek, ',');
	getline(f, A.session[0], ',');
	getline(f, A.session[1]);
	A.Schedule = A.session[0] + ';' + A.session[1] + '-' + A.DayOfWeek;
}

void Back_A_Semester(SchoolYear& S) {
	if (S.semester.Name.back() == '1' || S.semester.Name.back() == '0') {
		string year = "";
		for (int i = 0; i < 4; i++) {
			year += S.year[i];
		}
		int Y = atoi(year.c_str());
		Y--;
		S.year = to_string(Y) + "-" + year;
		S.semester.Name = "Semester3";
	}
	else {
		if (S.semester.Name.back() == '2') {
			S.semester.Name.pop_back();
			S.semester.Name.push_back('1');
		}
		else if (S.semester.Name.back() == '3') {
			S.semester.Name.pop_back();
			S.semester.Name.push_back('2');
		}
	}
}
void get_all_course(User& A, SchoolYear SY) {
	int i = 0;
	int count = 0;
	do {
		i = get_course(A, SY, 1);
		if (i == -1) {
			break;
		}
		Back_A_Semester(SY);
	} while (i != -1);
}

Course* get_course_of_student(User A, SchoolYear SY, int& n) {
	string fileName = "database/SchoolYear/" + SY.year + '/' + SY.semester.Name + "/course_info" + csv_tail;
	ifstream f;
	f.open(fileName, ios::in);
	if (!f.good()) {
		return NULL;
	}
	string temp;
	get_course(A, SY);
	if (A.info.phead == NULL) {
		return NULL;
	}
	n = 0;
	MarkNode* count = A.info.phead;
	while (count != NULL) {
		n++;
		count = count->pNext;
	}
	count = A.info.phead;
	Course* M = new Course[n];
	int i = 0;
	while (i < n && !f.eof()) {
		getline(f, M[i].ID_course, ',');
		if (_strcmpi(M[i].ID_course.c_str(), count->data.ID.c_str()) == 0) {
			getline(f, M[i].name, ',');
			getline(f, M[i].teacher, ',');
			getline(f, temp, ',');
			M[i].Num_of_creadit = atoi(temp.c_str());
			getline(f, temp, ',');
			M[i].Max_student = atoi(temp.c_str());
			getline(f, M[i].DayOfWeek, ',');
			getline(f, M[i].session[0], ',');
			getline(f, M[i].session[1]);
			i++;
			count = count->pNext;
			f.close();
			f.open(fileName, ios::in);
		}
		else {
			getline(f, temp);
		}
	}
	return M;
}
Data* read_file_student_info_of_course(SchoolYear SY, string IDcourse, int& n) {
	string fileName = "database/SchoolYear/" + SY.year + '/' + SY.semester.Name + "/Course/" + IDcourse + csv_tail;
	ifstream f;
	f.open(fileName, ios::in);
	if (!f.good()) {
		return NULL;
	}
	n = countLine(fileName) - 1;
	Data* M = new Data[n];
	string temp;
	getline(f, temp);
	for (int i = 0; i < n; i++) {
		getline(f, M[i].IDstd, ',');
		getline(f, M[i].name, ',');
		getline(f, M[i].Bir, ',');
		getline(f, M[i].sex, ',');
		getline(f, M[i].IDsocial);
		M[i].NO_inclass = i + 1;
	}
	f.close();
	return M;
}
