#include "Menu.h"
#include "Staff.h"
#include "Login.h"
#include "System_Function.h"
#include "List_Class.h"


void DrawBlank(){}// không draw gì cả

void DrawStaffMenu() {
    SchoolYear SchYr;
	determineYearSemesterNow(SchYr.year, SchYr.semester.Name);

	drawRectangle(3, 1, 115, 8, 11);
	drawRectangle(3, 23.5, 115, 5, 11);
	drawRectangle(3, 22, 115, 1, 11);

	drawRectangle(3, 9, 115, 14, 15);
	drawRectangle(3, 26, 115, 1, 11);	
    drawRectangle(3, 26, 115, 1, 11);
	textBgColor(2, 11);
    
    DrawTextFile("_assets\\menu_staff.txt", 20, 1);
    DrawTextFile("_assets\\login_bg2.txt", 9, 23);

    printtext("     " + SchYr.semester.Name + " - " + SchYr.year + "     ", 44, 8);
    textBgColor(0, 11);
}

void DrawStudentMenu()
{
	SchoolYear SchYr;
	determineYearSemesterNow(SchYr.year, SchYr.semester.Name);

	drawRectangle(3, 1, 115, 8, 11);
	drawRectangle(3, 23.5, 115, 5, 11);
	drawRectangle(3, 22, 115, 1, 11);

	drawRectangle(3, 9, 115, 14, 15);
	drawRectangle(3, 26, 115, 1, 11);
	textBgColor(2, 11);

	DrawTextFile("_assets\\menu_student.txt", 10, 1);
	DrawTextFile("_assets\\login_bg2.txt", 9, 23);

	printtext("     " + SchYr.semester.Name + " - " + SchYr.year + "     ", 44, 8);
	textBgColor(0, 2);
}

void DrawDeleteCourse()
{
	textBgColor(4, 6);
	DrawTextFile("_assets\\menu_delete_course.txt", 20, 5);
	printtext("Choose the course you want to delete. Enter to choose.", 35, 28);
}

void DrawChangeYear()
{
	textColor(46);
	DrawTextFile("_assets\\menu_change_year.txt", 15, 4);
	textColor(496);
}

void DrawChangeSemester()
{
	textColor(46);
	DrawTextFile("_assets\\menu_change_semester.txt", 35, 5);
	textColor(496);
}


void DrawSuccessfulEnrol()
{
	textBgColor(6, 0);
	DrawTextFile("_assets\\menu_successful.txt", 20, 15);
	textBgColor(0, 15);
}

void DrawFailEnrol()
{
	textBgColor(6, 0);
	DrawTextFile("_assets\\menu_failed_enrol.txt", 35, 15);
	printtext("        The course has been registered before.           ", 35, 21);
	printtext("                                                         ", 35, 22);
	textBgColor(0, 15);
}

void DrawEnrolCourse()
{
	textBgColor(4, 6);
	DrawTextFile("_assets\\menu_enrol_course.txt", 20, 3);
	printtext("Choose the course you want to enrol. Enter to choose.", 35, 28);
}

void DrawListCourse()
{
	textBgColor(4, 6);
	DrawTextFile("_assest\\menu_list_course.txt", 30, 2);
}
void StaffMenu(User& staff)
{
	showPointer();
	bool isExit = false;
	SchoolYear SY;
	determineYearSemesterNow(SY.year, SY.semester.Name);
	read_info(staff, SY);
	int option;
	string MenuStaff[] = { "YOUR INFO","CREATE NEW ONE","CLASS","COURSE","LOG OUT" };
	string MenuStaff1[] = { "1. Profile", "2. Change password","3. Back" };
	string MenuStaff2[] = {"1. Create school year","2. Create semester ", 
		"3. Create course registration session", "4. Create course",
		"5. Create Class","6. Add Student to class","7. Back"
	};
	string MenuStaff4[] = {
	"1. View List Course And List Student in Course",
	"2. Delete or Edit Course info","3. Back to Menu" };
	do
	{
		showPointer();
		system("cls");
		gotoxy(0, 7);
		drawMenu(MenuStaff, 5, 50, 12, 1, &DrawStaffMenu);
		option = Select(5, MenuStaff, 50, 12, 1);
		switch (option)
		{
		case 0: {
			system("cls");
			drawMenu(MenuStaff1, 3, 50, 13, 2, &DrawStaffMenu);
			int option1 = Select(3, MenuStaff1, 50, 13, 2);
			switch (option1)
			{
			case 0: {
				Output_info(staff);
				break;
			}
			case 1: {
				Change_Password(staff);
				break;
			}
			case 2: {
				break;
			}
			}
			break;
		}

		case 1: {
			system("cls");

			drawMenu(MenuStaff2, 7, 44, 9, 1, &DrawStaffMenu);
			int option1 = Select(7, MenuStaff2, 44, 9, 1);
			switch (option1)
			{
			case 0: {
				addSchoolYear(SY);
				break;
			}
			case 1: {
				addSemester(SY.year, SY.semester.Name);
				break;
			}
			case 2: {
				createRegistrationCourse();
				break;
			}
			case 3: {
				addCourse();
				break;
			}
			case 4: {
				RunMenuCreateClass();
				break;
			}
			case 5:
			{
				RunMenuAddInfoStudentToClass();
				break;
			}
			default:
				break;
			}
			break;
		}

		case 2:
		{
			system("cls");
			listClass(staff, SY, &showStudentInclass);
			break;
		}
		case 3: {
			system("cls");
			drawMenu(MenuStaff4, 3, 40, 12, 2, &DrawStaffMenu);
			int option1 = Select(3, MenuStaff4, 40, 12, 2);
			switch (option1)
			{
			case 0: {
				system("cls");
				viewStudentInCourse(staff, SY);
				textBgColor(0, 15);
				break;
			}
			case 1: {
				listCourse(staff, SY.year, SY.semester.Name);
				break;
			}
			case 2: {
				break;
			}
			}
			break;
		}

		case 4:
			isExit = true;
			break;
		}
	} while (!isExit);
	LoginLoop(staff);
}

void StudentMenu(User& student)
{
	showPointer();
	SchoolYear SchYr;
	determineYearSemesterNow(SchYr.year, SchYr.semester.Name);
	if (SchYr.semester.Name == "Semester0") {
		drawRectangle(3, 14, 115, 3, 4);
		printtext("The school year hasn't started yet ", 40, 15);
		Sleep(1800);
		LoginLoop(student);
		return;
	}
	read_info(student, SchYr);
	init_List_Mark(student.info.phead);
	bool isExit = false;
	int option;
	string MenuStudent[] = { "YOUR INFO", "COURSE" ,"LOG OUT" };
	string MenuStd1[] = { "1. Profile","2. Change password","3. Back" };
	string MenuStd2[] = { "1. Enroll course","2. Remove course","3. View list of course you enrolled","4. Back" };

	do
	{
		system("cls");
		drawMenu(MenuStudent, 3, 50, 12, 2, &DrawStudentMenu);
		option = Select(3, MenuStudent, 50, 12, 2);
		switch (option)
		{
		case 0: {
			system("cls");
			drawMenu(MenuStd1, 3, 50, 11, 2, &DrawStaffMenu);
			int option1 = Select(3, MenuStd1, 50, 11, 2);
			switch (option1)
			{
			case 0: {
				Output_info(student);
				break;
			}
			case 1: {
				Change_Password(student);
				break;
			}
			case 2: {
				break;
			}
			}
			break;
		}
		case 1: {
			system("cls");
			drawMenu(MenuStd2, 4, 45, 10, 2, &DrawStudentMenu);
			int option1 = Select(4, MenuStd2, 45, 10, 2);
			switch (option1)
			{
			case 0: {
				enroll_course(student, SchYr);
				try {
					int check = checkCourseSession();
					if (check == 1) {
						enroll_course(student, SchYr);
					}
					else {
						drawRectangle(35, 15, 50, 5, 4);
						textBgColor(15, 4);
						if (check == 0) printtext("NOT OPEN REGISTER COURSE YET", 45, 17);
						else if (check == -1) printtext("IT'S NOT THE TIME TO START YET", 45, 17);
						else printtext("It was late to register the course", 45, 17);
						Sleep(1800);
						textBgColor(0, 15);
					}
				}
				catch (const char* err) {
					string s = string(err);
					s.pop_back();
					s += " to enroll.";
					drawRectangle(3, 14, 115, 3, 4);
					printtext(s, 45, 15);
					textBgColor(0, 15);
					Sleep(1800);
				}
				break;
			}
			case 1: {
				//lenh xoa bot khoa hoc da dang ki
				try {
					int check = checkCourseSession();
					if (check == 1) {
						delete_course(student, SchYr);
					}
					else {
						drawRectangle(35, 15, 50, 5, 4);
						textBgColor(15, 4);
						if (check == 0) printtext("NOT OPEN REGISTER COURSE YET", 45, 17);
						else if (check == -1) printtext("IT'S NOT THE TIME TO START YET", 45, 17);
						else printtext("It was late to register the course", 45, 17);
						Sleep(1800);
						textBgColor(0, 15);
					}
				}
				catch (const char* err) {
					string s = string(err);
					s.pop_back();
					s += " to delete.";
					drawRectangle(3, 14, 115, 3, 4);
					printtext(s, 45, 15);
					textBgColor(0, 15);
					Sleep(1800);
				}
				break;
			}
			case 2: {
				DisPlay_Course_Of_Student(SchYr, student);
				break;
			}
			default: {
				break;
			}
			}
			break;
		}
		case 2: {
			isExit = true;
			break;
		}
		}
	} while (!isExit);
	LoginLoop(student);
}
