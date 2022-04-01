#include "Menu.h"
#include "Staff.h"
#include "Login.h"
#include "System_Function.h"

void DrawStaffMenu() {
    /*SchoolYear SchYr;
    DisplayYearSemester(SchYr.year, SchYr.semester.Name);*/

	drawRectangle(3, 1, 115, 8, 11);
	drawRectangle(3, 23.5, 115, 5, 11);
	drawRectangle(3, 22, 115, 1, 11);

	drawRectangle(3, 9, 115, 14, 15);
	drawRectangle(3, 26, 115, 1, 11);
    drawRectangle(3, 26, 115, 1, 11);
	textBgColor(2, 11);
    
    DrawTextFile("_assets\\menu_staff.txt", 20, 1);
    DrawTextFile("_assets\\login_bg2.txt", 9, 23);

    //printtext("     " + SchYr.semester.Name + " - " + SchYr.year + "     ", 43, 22);
    textBgColor(0, 2);
}

void DrawStudentMenu()
{
	/*SchoolYear SchYr;
	DisplayYearSemester(SchYr.year, SchYr.semester.Name);*/

	drawRectangle(3, 1, 115, 8, 11);
	drawRectangle(3, 23.5, 115, 5, 11);
	drawRectangle(3, 22, 115, 1, 11);

	drawRectangle(3, 9, 115, 14, 15);
	drawRectangle(3, 26, 115, 1, 11);
	textBgColor(2, 11);

	DrawTextFile("_assets\\menu_student.txt", 10, 1);
	DrawTextFile("_assets\\login_bg2.txt", 9, 23);

	//printtext("     " + SchYr.semester.Name + " - " + SchYr.year + "     ", 43, 22);
	textBgColor(0, 2);
}

void StaffMenu(User& staff)
{
	showPointer();
	bool isExit = false;
	SchoolYear SchYr;
	DisplayYearSemester(SchYr.year, SchYr.semester.Name);
	//read_info(user, SY);
	int option;
	string MenuStaff[] = { "YOUR INFO","NEW","CLASS INFO","COURSE INFO","RESULT OF STUDENTS","LOG OUT" };
	string MenuStaff1[] = { "1. Profile info", "2. Change password","3.Back to Menu" };
	string MenuStaff2[] = {
	"1. Create school - year",
	"2. Create semester ", "3. Create course registration session", "4. Create course",
	"5. Create Class","6. Add Student to class","7. Back to Menu"
	};
	string MenuStaff4[] = {
	"1. View List Course And List Student in Course",
	 "2. Delete or Edit Course info","3.Back to Menu" };
	string MenuStaff5[] = { "1. View and edit student's marks", "2. Export student list mark", "3. Import student list mark", "4. Back to Menu" };
	do
	{
		showPointer();
		system("cls");
		gotoxy(0, 7);

		//drawMenu(MenuStaff, 6, 50, 10, 1, &DrawStaffMenu);
		option = Select(6, MenuStaff, 50, 10, 1);
	} while (!isExit);
	LoginLoop(staff);
}

void StudentMenu(User& student)
{
	showPointer();
	SchoolYear SchYr;
	//DisplayYearSemester(SchYr.year, SchYr.semester.Name);
	if (SchYr.semester.Name == "Semester0") {
		drawRectangle(3, 14, 115, 3, 4);
		printtext("The school year hasn't started yet ", 40, 15);
		Sleep(1800);
		LoginLoop(student);
		return;
	}
	//read_info(user, SY);
	//init_List_Mark(user.info.phead);
	bool isExit = false;
	int option;
	string MenuStudent[] = { "YOUR INFO", "COURSE" , "YOUR RESULTS","LOG OUT" };
	string MenuStd1[] = { "1. Profile info","2. Change password","3.Back to Menu" };
	string MenuStd2[] = { "1. Enroll courses","2. Remove course","3. View your list of course","4.Back to Menu" };

	do
	{
		system("cls");
		//drawMenu(MenuStudent, 4, 50, 10, 2, &DrawStudentMenu);
		option = Select(4, MenuStudent, 50, 10, 2);
	} while (!isExit);
	DisplayYearSemester(SchYr.year, SchYr.semester.Name);
	LoginLoop(student);
}
