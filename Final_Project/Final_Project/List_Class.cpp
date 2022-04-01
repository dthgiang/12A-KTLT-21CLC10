#include "List_Class.h"
#include "System_Function.h"
using namespace std;


void drawMenuView() {
	textBgColor(0, 5);
	DrawTextFile("_assets\\objects\\menuview.txt", 40, 4);
}
Database Input()
{
	Database data;
	gotoxy(53, 17);
	cout << "ENTER STUDENT INFOR" << endl;
	cin.ignore();
	gotoxy(58, 18);
	cout << "ID:"; getline(cin, data.ID);
	gotoxy(58, 19);
	cout << "Full Name:"; getline(cin, data.name);
	gotoxy(58, 20);
	cout << "Birth of date:"; getline(cin, data.Birth);
	gotoxy(58, 21);
	cout << "Sex:"; getline(cin, data.sex);
	gotoxy(58, 22);
	cout << "Social ID:"; getline(cin, data.IDsocial);
	return data;
}

int CheckRowInFile(string filename)
{
	fstream f;
	f.open(filename, ios::in);
	int count = -1;
	string name;
	while (!f.eof())
	{
		getline(f, name);
		count++;
	}
	return count;
}


void drawASCIIMenuView()
{
	//textBgColor(0, 6);
	//DrawTextFile("_assets\\objects\\class.txt", 40, 4);
}

string CheckSem()
{
	fstream Fclass;
	Fclass.open("_assets//year-semester.csv");
	string YearTem, SemTem;
	string CheckSem;
	while (!Fclass.eof())
	{
		getline(Fclass, YearTem, ',');
		Fclass >> SemTem;
		CheckSem = SemTem;
	}
	Fclass.close();
	return CheckSem;
}

void ImportRandom(string& YearCourse, string& Class)
{
	fstream ofs, ifs;
	string NameClass = "_assets//SchoolYear//" + YearCourse + "//" + Class + ".csv";
	ofs.open(NameClass, ios::app);
	ifs.open("_assets//InforNewStudent.csv", ios::in);
	string  NameSt, BirthSt, SexSt, IdSocialSt;
	int count = CheckRowInFile(NameClass);
	int IDSt;
	string CheckYear = { YearCourse };
	string CheckNameYear = { CheckYear[2] , CheckYear[3] };
	int MasoNam;
	MasoNam = atoi(CheckNameYear.c_str()) * 1000000;
	string str = { Class };
	string CheckNameClass = { str[2] , str[3] , str[4] };
	string CheckSTTClass = { str[5] };
	if (CheckNameClass == "CTT")
	{
		if (CheckSTTClass == "1")
		{
			IDSt = MasoNam + 120000;
		}
		if (CheckSTTClass == "2")
		{
			IDSt = MasoNam + 120100;
		}
		if (CheckSTTClass == "3")
		{
			IDSt = MasoNam + 120200;
		}
		if (CheckSTTClass == "4")
		{
			IDSt = MasoNam + 120300;
		}

	}
	if (CheckNameClass == "SHH")
	{
		if (CheckSTTClass == "1")
		{
			IDSt = MasoNam + 150000;
		}
		if (CheckSTTClass == "2")
		{
			IDSt = MasoNam + 150100;
		}
		if (CheckSTTClass == "3")
		{
			IDSt = MasoNam + 150200;
		}
		if (CheckSTTClass == "4")
		{
			IDSt = MasoNam + 150300;
		}
	}
	if (CheckNameClass == "HOH")
	{
		if (CheckSTTClass == "1")
		{
			IDSt = MasoNam + 170000;
		}
		if (CheckSTTClass == "2")
		{
			IDSt = MasoNam + 170100;
		}
		if (CheckSTTClass == "3")
		{
			IDSt = MasoNam + 170200;
		}
		if (CheckSTTClass == "4")
		{
			IDSt = MasoNam + 170300;
		}
	}
	if (CheckNameClass == "TTH")
	{
		if (CheckSTTClass == "1")
		{
			IDSt = MasoNam + 110000;
		}
		if (CheckSTTClass == "2")
		{
			IDSt = MasoNam + 110100;
		}
		if (CheckSTTClass == "3")
		{
			IDSt = MasoNam + 110200;
		}
		if (CheckSTTClass == "4")
		{
			IDSt = MasoNam + 110300;
		}
	}
	string NumberOfStudent;
	fstream file2;
	file2.open("_assets//SchoolYear//" + YearCourse + "//class_info.csv", ios::in);
	string stt2, NameClass2, major2, number2, year2;
	while (!file2.eof())
	{
		getline(file2, stt2, ',');
		getline(file2, NameClass2, ',');
		getline(file2, major2, ',');
		getline(file2, number2, ',');
		file2 >> year2;
		if (Class == NameClass2)
		{
			NumberOfStudent = number2;
		}
	}
	int CheckNumberOfStudent = atoi(NumberOfStudent.c_str());
	int countFile = CheckRowInFile("_assets//InforNewStudent.csv");
	if (countFile < CheckNumberOfStudent)
	{
		gotoxy(43, 21);
		cout << "FILE INPUT IS FAIL, DON'T IMPORT INFO TO CLASS" << endl;
		Sleep(1000);
	}
	else
	{

		while (count != (CheckNumberOfStudent))
		{
			fstream finput;
			finput.open("_assets//login_info.csv", ios::app);
			int MSSV = IDSt + count;
			ofs << endl;
			ofs << count + 1 << ",";
			ofs << MSSV << ",";
			finput << endl << MSSV << "," << MSSV << "," << "1" << "," << Class;
			getline(ifs, NameSt, ',');
			ofs << NameSt << ",";
			getline(ifs, BirthSt, ',');
			ofs << BirthSt << ",";
			getline(ifs, SexSt, ',');
			ofs << SexSt << ',';
			getline(ifs, IdSocialSt);
			ofs << IdSocialSt;
			count++;
			finput.close();
		}
		ifs.close();
		ofs.close();
		string arr[10000];
		fstream f1;
		f1.open("_assets//InforNewStudent.csv", ios::in);

		while (!f1.eof())
		{
			for (int i = 0; i <= countFile; i++)
			{
				getline(f1, arr[i]);
			}
		}
		f1.close();
		fstream f2;
		f2.open("_assets//InforNewStudent.csv", ios::out);
		for (int i = CheckNumberOfStudent; i < countFile; i++)
		{
			f2 << arr[i] << endl;
		}
		f2.close();
	}
	string CheckSe = CheckSem();
	fstream F, FILE;
	string S = "_assets//SchoolYear//" + YearCourse + "//Semester" + CheckSe + "//Class//" + Class + ".csv";
	F.open(S, ios::app);
	int countF = CheckRowInFile(S);
	string SS = "_assets//SchoolYear//" + YearCourse + "//" + Class + ".csv";
	FILE.open(SS, ios::in);
	string CheckNo, CheckID, CheckName, CheckBirth, CheckSex, CheckIDso;
	while (!FILE.eof())
	{
		getline(FILE, CheckNo, ',');
		getline(FILE, CheckID, ',');
		getline(FILE, CheckName, ',');
		getline(FILE, CheckBirth, ',');
		getline(FILE, CheckSex, ',');
		FILE >> CheckIDso;
		int AtoiID = atoi(CheckID.c_str());
		if (AtoiID != 0)
		{
			if (countF == 0)
			{
				F << CheckID;
				countF++;
			}
			else
			{
				F << endl << CheckID;
			}
		}
	}
}

void CreateAutoClassAndImportRandomInfo()
{
	string name;
	system("cls");
	drawASCIIMenuView();
	string Year;
	textBgColor(0, 11);
	drawRectangle(35, 12, 60, 12, 11);
	fstream fs;
	fs.open("_assets//year-semester.csv", ios::in);
	string tempYear;
	string tempSemester;
	while (!fs.eof())
	{
		getline(fs, tempYear, ',');
		getline(fs, tempSemester);
		Year = tempYear;
	}
	{
		textBgColor(0, 11);
		gotoxy(43, 13);
		cout << "Enter Name Abbreviations Of Class(CTT,HOH,TTH,SHH): ";
		drawRectangle(43, 14, 45, 1, 15);
		gotoxy(43, 14);
		getline(cin, name);

		if (name == "CTT" || name == "HOH"
			|| name == "TTH" || name == "SHH")
		{
			fstream file1;
			bool check = true;
			file1.open("_assets//SchoolYear//" + Year + "//class_info.csv", ios::in);
			string stt, NameClass, major, number, year;
			while (!file1.eof())
			{
				getline(file1, stt, ',');
				getline(file1, NameClass, ',');
				getline(file1, major, ',');
				getline(file1, number, ',');
				file1 >> year;
				if (name == NameClass)
				{
					check = false;
				}
			}
			if (check == false)
			{
				gotoxy(43, 16);
				cout << "CLASS EXIST! PLEASE TRY AGAIN" << endl;
			}
			if (check == true)
			{
				string NameMajor;
				textBgColor(0, 11);
				gotoxy(43, 15);
				cout << "Enter Name Of Major: ";
				drawRectangle(43, 16, 45, 1, 15);
				gotoxy(43, 16);
				getline(cin, NameMajor);
				int numberStudent;
				textBgColor(0, 11);
				gotoxy(43, 17);
				cout << "Enter Number Of Student(Max=100): ";
				drawRectangle(43, 18, 45, 1, 15);
				gotoxy(43, 18);
				cin >> numberStudent;
				if (numberStudent <= 100)
				{
					int NumberOfClass;
					textBgColor(0, 11);
					gotoxy(43, 19);
					cout << "Enter Number Of Class(Max = 4): ";
					drawRectangle(43, 20, 45, 1, 15);
					gotoxy(43, 20);
					cin >> NumberOfClass;
					if (NumberOfClass <= 4)
					{
						string str = { Year };
						string YearStudent = { Year[0],Year[1],Year[2],Year[3] };

						fstream file;
						string filename = "_assets//SchoolYear//" + Year + "//class_info.csv";
						string CheckYear = { Year[2], Year[3] };
						for (int i = 1; i <= NumberOfClass; i++)
						{
							string s = to_string(i);
							string NameClasses = CheckYear + name + s;
							string FileName = "_assets//SchoolYear//" + Year + "//" + NameClasses + ".csv";
							fstream f1;
							f1.open(FileName, ios::out);
							f1 << "No" << "," << "ID" << "," << "Name" << "," << "Birth" << "," << "Sex" << "," << "IDSocial";;
							f1.close();
							int count = CheckRowInFile(filename);
							file.open("_assets//SchoolYear//" + Year + "//class_info.csv", ios::app);
							file << endl << count << "," << CheckYear << name << i << "," << NameMajor << "," << numberStudent << "," << YearStudent;
							file.close();
							ImportRandom(Year, NameClasses);
						}

						gotoxy(43, 23);
						cout << "CREATE CLASS SUCCESSFUL" << endl;
						Sleep(1000);
					}
					else
					{
						gotoxy(43, 21);
						cout << "Max Number Of Class is 4! Try Again!!!" << endl;
						Sleep(1000);
					}
				}
				else
				{
					gotoxy(43, 20);
					cout << "Max Number Of Student is 100! Try Again!!!" << endl;
					Sleep(1000);
				}


			}
		}
		else
		{
			gotoxy(43, 17);
			cout << "Name abbreviations class is malformed!! Try again" << endl;
			Sleep(1000);
		}
	}
}

void CreateNewClass() {
	string name, year;
	string tYear, tSemester;
	fstream f;
	system("cls");
	drawMenuView();
	textBgColor(0, 11);
	drawRectangle(34, 12, 60, 12, 11);
	f.open("_assets//year-semester.csv");
	while (!f.eof()) {
		getline(f, tYear, ',');
		getline(f, tSemester);
		year = tYear;
	}
	textBgColor(0, 11);
	gotoxy(43, 14);
	drawRectangle(43, 15, 45, 1, 15);
	cout << "Enter type of class (Ex: CTT, HOH,...): ";
	getline(cin, name);
	string str = name;
	string checkTypeClass = { str[2] , str[3] , str[4] };
	string checkStt = { str[5] };
	if (checkTypeClass == "CTT" || checkTypeClass == "HOH" || checkTypeClass == "TTH" || checkTypeClass == "SHH") {
		if (checkStt == "1" || checkStt == "2" || checkStt == "3" || checkStt == "4") {
			fstream f1;
			string stt, NameClass, major, number, year;
			bool check = true;
			f1.open("_assets//SchoolYear//" + year + "//class_info.csv");
			while (f1.eof()) {
				getline(f1, stt, ',');
				getline(f1, NameClass, ',');
				getline(f1, major, ',');
				getline(f1, number, ',');
				f1 >> year;
				if (name == NameClass) check = false;
			}
			if (check == false) {
				printtext("Class already exists, try again\n", 43, 17);
				Sleep(1000);
			}
			else {
				string nameMajor;
				textBgColor(0, 11);
				gotoxy(43, 16); cout << "Enter name of major: ";
				drawRectangle(43, 17, 45, 1, 15); gotoxy(43, 17);
				getline(cin, nameMajor);
				if (nameMajor == "") Sleep(1000);
				else {
					int nStu;
					textBgColor(0, 11);
					printtext("Enter the number of Student: ", 43, 18);
					drawRectangle(43, 19, 45, 1, 15);
					gotoxy(43, 19); cin >> nStu;
					if (nStu > 100) {
						printtext("n <= 100", 43, 21);
						Sleep(100);
					}
					else {
						string str = { year };
						string yearStudent = { year[0],year[1],year[2],year[3] };
						ofstream fA, fB;
						int count = CheckRowInFile("_assets//SchoolYear//" + year + "//class_info.csv");
						fA.open("_assets//SchoolYear//" + year + "//class_info.csv", ios::app);
						fA << endl << count + 1 << "," << name << "," << nameMajor << "," << nStu << "," << yearStudent;
						fB.open("_assets//SchoolYear//" + year + "//" + name + ".csv");
						fB << "No" << "," << "ID" << "," << "Name" << "," << "Birth" << "," << "Sex" << "," << "IDSocial";
						printtext("SUCESS!!", 43, 23);
						while (1)
						{
							string CheckSe = CheckSem();
							if (CheckSe == "0") break;
							else
							{
								string CreateClass = "_assets//SchoolYear//" + year + "//Semester" + CheckSe + "//Class//" + name + ".csv";
								fstream fCreate;
								fCreate.open(CreateClass, ios::out);
								fCreate.close();
							}
							break;
						}
						fA.close(); fB.close();
					}
				}
			}
		}
		else Sleep(1000);
	}
	else Sleep(1000);
}

int RunMenuCreateClass()
{
	char ch;
	int command;

	while (true)
	{
		showPointer();
		system("cls");

		gotoxy(40, 12);
		string MenuView[] = { "1. Create 1 Class",
			"2. Create Auto Classes And Import Info",
			"3. Exit" };
		//drawMenu(MenuView, 3, 47, 12, 1, &drawASCIIMenuView);
		command = Select(3, MenuView, 47, 12, 1);
		switch (command)
		{
		case 0:
		{
			system("cls");
			CreateNewClass();
			system("cls");
			break;
		}
		case 1:
		{
			system("cls");
			CreateAutoClassAndImportRandomInfo();
			system("cls");
			break;
		}
		case 2:
		{
			textBgColor(10, 11);
			printtext("YOU WANT TO EXIT, PRESS ENTER TO BACK TO MENU !!!", 40, 20);
			ch = _getch();
			textBgColor(0, 15);
			return 0;
		}
		}
	}
}
