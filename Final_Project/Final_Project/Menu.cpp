#include "Menu.h"
#include "Staff.h"
#include "Login.h"
#include "System_Function.h"
#include "List_Class.h"

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

void DrawEditScore()
{
	textBgColor(19, 0);
	DrawTextFile("_assets\\menu_edit_score.txt", 20, 4);
	textBgColor(0, 15);
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

		drawMenu(MenuStaff, 6, 50, 10, 1, &DrawStaffMenu);
		option = Select(6, MenuStaff, 50, 10, 1);
		switch (option)
		{
		case 0: {
			system("cls");
			drawMenu(MenuStaff1, 3, 50, 11, 2, &DrawStaffMenu);
			int option1 = Select(3, MenuStaff1, 50, 11, 2);
			switch (option1)
			{
			case 0: {
				// lenh show thong tin 
				Output_info(staff);
				break;
			}
			case 1: {
				// lenh thay mat khau
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

			drawMenu(MenuStaff2, 7, 40, 9, 1, &DrawStaffMenu);
			int option1 = Select(7, MenuStaff2, 40, 9, 1);
			switch (option1)
			{
			case 0: {
				// lenh tao nam
				//addSchoolYear(SY);
				break;
			}
			case 1: {
				//lenh them hoc ki
				addSemester(SchYr.year, SchYr.semester.Name);
				break;
			}
			case 2: {
				// tao phien dang ki khoa hoc
				createRegistrationCourse();
				break;
			}
			case 3: {
				// lenh them khoa hoc
				addCourse();
				break;
			}
			case 4: {
				// lenh them lop hoc
				RunMenuCreateClass();
				break;
			}
			case 5:
			{

				system("cls");
				//AddStudentToClass();
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
			//xem danh sach lop hoc va danh sach sinh vien trong lop
			listClass(staff, SchYr, &showStudentInclass);
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
				//xem danh sach khoa hoc va danh sach sinh vien trong khoa
				viewStudentInCourse(staff, SchYr);
				textBgColor(0, 15);
				break;
			}
			case 1: {
				//view danh sachs hoc phan
				listCourse(staff, SchYr.year, SchYr.semester.Name);
				break;
			}
			case 2: {
				break;
			}
			}
			break;
		}
		case 4:
			/*system("cls");
			RunMenuViewListClass();
			break;*/
		{
			bool checkMenu = true;
			do {
				system("cls");
				drawMenu(MenuStaff5, 4, 40, 10, 2, &DrawStaffMenu);
				int option1 = Select(4, MenuStaff5, 40, 10, 2);
				switch (option1)
				{
				case 0: //edit diem sinh vien
				{
					system("cls");
					string edit[] = { "1. From List Class.","2. From List Course.","3. Exit to Menu." };
					drawMenu(edit, 3, 45, 20, 2, &DrawEditScore);
					int choose = Select(3, edit, 45, 20, 2);
					switch (choose)
					{
					case 0: {
						listClass(staff, SchYr, &showScoreOfClass);
						break;
					}
					case 1: {
						try {
							Course* SLC = select_course(staff, SchYr, &read_file_List_course, &DrawListCourse);
							if (SLC == NULL) {
								break;
							}
							edit_score_in_list_course(staff, SchYr, SLC->ID_course);
						}
						catch (const char* err) {
							drawRectangle(3, 14, 115, 3, 4);
							printtext(err, 50, 15);
							textBgColor(0, 15);
							Sleep(1800);
						}
						break;
					}
					default:
						break;
					}
					break;
				}
				case 1: {
					//xuat diem hoc sinh vao file
					exportScoreboardInterface(staff, SchYr.year, SchYr.semester.Name, 2, 1);
					break;
				}
				case 2: {
					//xuat diem hoc sinh vao file
					importScoreBoardUI();
					break;
				}
				case 3: {
					checkMenu = false;
					break;
				}
				}
			} while (checkMenu == true);
			break;
		}
		case 5:
			isExit = true;
			break;
			//default: std::cout << "your choice is invalid!!!\n";
		}
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
		drawMenu(MenuStudent, 4, 50, 10, 2, &DrawStudentMenu);
		option = Select(4, MenuStudent, 50, 10, 2);
		switch (option)
		{
		case 0: {
			system("cls");
			drawMenu(MenuStd1, 3, 50, 11, 2, &DrawStaffMenu);
			int option1 = Select(3, MenuStd1, 50, 11, 2);
			switch (option1)
			{
			case 0: {
				// lenh show thong tin 
				Output_info(student);
				break;
			}
			case 1: {
				// lenh thay mat khau
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
				//enroll_course(user, SY);
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
			// lenh show bang diem
			DisPlay_Mark_Of_Student(SchYr, student);
			break;
		}
		case 3: {
			isExit = true;
			break;
		}
		}
	} while (!isExit);
	//DisplayYearSemester(SchYr.year, SchYr.semester.Name);
	LoginLoop(student);
}
