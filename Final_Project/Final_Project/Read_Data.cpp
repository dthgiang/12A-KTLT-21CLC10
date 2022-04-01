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