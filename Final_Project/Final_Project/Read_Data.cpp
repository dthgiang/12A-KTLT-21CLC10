#include "Read_Data.h"

Course* Read_File_List_Course(User A, SchoolYear SchYr, int& n) {
	string file = "file_save/SchoolYear/" + SchYr.year + '/' + SchYr.semester.Name + "/course_info" + csv_tail;
	ifstream fi;
	fi.open(file, ios::in);
	if (!fi.good()) {
		drawRectangle(3, 14, 115, 3, 4);
		printtext("Can't open information file.", 47, 15);
		textBgColor(0, 15);
		Sleep(1800);
		return NULL;
	}
	n = countLine(file) - 1;
	if (n == 0) {
		return NULL;
	}
	Course* M = new Course[n];
	string temp;
	getline(fi, temp);
	for (int i = 0; i < n; i++) {
		getline(fi, M[i].ID_course, ',');
		getline(fi, M[i].name, ',');
		getline(fi, M[i].teacher, ',');
		getline(fi, temp, ',');
		M[i].Num_of_creadit = atoi(temp.c_str());
		getline(fi, temp, ',');
		M[i].Max_student = atoi(temp.c_str());
		getline(fi, M[i].DayOfWeek, ',');
		getline(fi, M[i].session[0], ',');
		getline(fi, M[i].session[1]);
	}
	fi.close();
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

int get_course(User& A, SchoolYear s_y, int flag)
{
	ifstream f;
	string semester_path = "file_save/SchoolYear/" + s_y.year + '/' + s_y.semester.Name + '/';
	string class_path = semester_path + "Class/";
	string course_path = semester_path + "Course/";
	string fileName = class_path + A.info.Class + csv_tail;
	bool IDflag = false;
	f.open(fileName, ios::in);
	if (!f.is_open()) {
		return -1;
	}
	if (flag == 0) {
		init_List_Mark(A.info.phead);
	}
	while (f.eof() == false) {

		string temp1;
		getline(f, temp1);
		size_t found = temp1.find(",");
		if (found == std::string::npos) {
			if (_strcmpi(temp1.c_str(), A.info.IDstd.c_str()) != 0) {
				continue;
			}
			else {
				return -2;
			}
		}
		int length = f.tellg();
		if (length == -1) {
			f.close();
			f.open(fileName, ios::in);
			f.seekg(0, ios::end);
			int a = f.tellg();
			f.seekg(a - temp1.length(), ios::beg);
		}
		else {
			f.seekg(length - temp1.length() - 2, ios::beg);
		}
		string temp;
		getline(f, temp, ',');
		if (temp.compare(A.info.IDstd) != 0) {
			getline(f, temp);
		}
		else {
			string temp1;
			getline(f, temp1);
			string IDtemp = "";
			for (int i = 0; i < temp1.length(); i++) {
				if (temp1[i] == ',' || i == temp1.length() - 1)
				{
					if (i == temp1.length() - 1) {
						IDtemp += temp1[i];
					}
					ifstream fi;
					string fileName = "file_save/SchoolYear/" + s_y.year + "/" + s_y.semester.Name + "/course_info.csv";
					fi.open(fileName, ios::in);
					string temp;
					string num_of_creadit;
					while (!fi.eof()) {
						getline(fi, temp, ',');
						if (_strcmpi(temp.c_str(), IDtemp.c_str()) == 0) {
							getline(fi, temp, ',');
							getline(fi, num_of_creadit, ',');
							getline(fi, num_of_creadit, ',');
							break;
						}
						else {
							getline(fi, temp);
						}
					}
					add_Tail_List_Mark(A.info.phead, IDtemp, temp, num_of_creadit);
					IDtemp = "";
					fi.close();
				}
				else if (temp1[i] != ',') {
					IDtemp += temp1[i];
				}
			}
			f.close();
			return 0;
		}
	}

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

void delete_Mark_node(MarkNode*& head, string ID)
{
	MarkNode** res = &head;
	while (*res != NULL) {
		MarkNode* temp = *res;
		if (_strcmpi(temp->data.ID.c_str(), ID.c_str()) == 0) {
			*res = temp->pNext;
			delete (temp);
		}
		else
			res = &(temp->pNext);
	}
}

void init_List_Mark(MarkNode*& head)
{
	head = NULL;
}

void add_Tail_List_Mark(MarkNode*& head, string ID, string name, string num_of_creadit)
{
	MarkNode* n1 = new MarkNode;
	n1->data.ID = ID;
	n1->data.Name = name;
	n1->data.C = num_of_creadit; // so tin chi
	n1->pNext = NULL;
	MarkNode* temp = head;
	if (head == NULL) {
		head = n1;
		return;
	}
	else {
		while (temp->pNext != NULL) {
			temp = temp->pNext;
		}
		temp->pNext = n1;
	}
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
