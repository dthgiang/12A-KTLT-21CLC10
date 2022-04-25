#include "List_Class.h"
#include "System_Function.h"
using namespace std;

void drawASCIIMenuView();
Database Input()
{
	drawBoder(50, 16, 30, 7, 1);
	Database data;
	gotoxy(55, 17);
	cout << "INPUT INFORMATION STUDENT" << endl;
	gotoxy(55, 18);
	cout << "Student id:";
	cin.ignore();
	getline(cin, data.ID);
	gotoxy(55, 19);
	cout << "Name:";
	getline(cin, data.name);
	gotoxy(55, 20);
	cout << "Birth:";
	getline(cin, data.Birth);
	gotoxy(55, 21);
	cout << "Sex:";
	getline(cin, data.sex);
	gotoxy(55, 22);
	cout << "IDsocial:";
	getline(cin, data.IDsocial);
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


string CheckSem()
{
	fstream Fclass;
	Fclass.open("database//year-semester.csv");
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
void CreateClassInSemester(string& Year, string& name)
{
	string CheckSe = CheckSem();
	if (CheckSe == "0")
	{
		return;
	}
	else
	{
		string CreateClass = "database//HCMUS//" + Year + "//Semester" + CheckSe + "//Class//" + name + csv_tail;
		fstream fCreate;
		fCreate.open(CreateClass, ios::out);

		fCreate.close();
	}
}
void CreateNewClass()
{
	system("cls");
	string name;
	drawASCIIMenuView();
	string Year;
	textBgColor(0, 11);
	drawRectangle(35, 12, 60, 12, 19);
	fstream fs;
	fs.open("database//year-semester.csv", ios::in);
	string tempYear;
	string tempSemester;
	while (!fs.eof())
	{
		getline(fs, tempYear, ',');
		getline(fs, tempSemester);
		Year = tempYear;
	}
	{
		textBgColor(0, 19);
		gotoxy(43, 14);
		cout << "Enter Name Of Class (CTT,CLC,VP,SHH, for ex: 20HOH1):";
		drawRectangle(43, 15, 45, 1, 15);
		gotoxy(43, 15);
		getline(cin, name);
		string str = { name };
		string CheckNameClass = { str[2] , str[3] , str[4] };
		string CheckSTTClass = { str[5] };
		if (CheckNameClass == "CTT" || CheckNameClass == "HOH"
			|| CheckNameClass == "VP" || CheckNameClass == "SHH")
		{
			if (CheckSTTClass == "1" || CheckSTTClass == "2"
				|| CheckSTTClass == "3" || CheckSTTClass == "4")
			{
				fstream file1;
				bool check = true;
				file1.open("database//HCMUS//" + Year + "//class_info.csv", ios::in);
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
					gotoxy(43, 17);
					cout << "CLASS EXIST! PLEASE TRY AGAIN" << endl;
					Sleep(1000);
				}
				if (check == true)
				{

					string NameMajor;
					textBgColor(0, 19);
					gotoxy(43, 16);
					cout << "Enter Name Of Major: ";
					drawRectangle(43, 17, 45, 1, 15);
					gotoxy(43, 17);
					getline(cin, NameMajor);
					if (NameMajor == "")
					{
						gotoxy(43, 19);
						cout << "Name Major is malformed!! Try again" << endl;
						Sleep(1000);
					}
					else
					{
						int numberStudent;
						textBgColor(0, 19);
						gotoxy(43, 18);
						cout << "Enter Number Of Student(Max=50): ";
						drawRectangle(43, 19, 45, 1, 15);
						gotoxy(43, 19);
						cin >> numberStudent;

						if (numberStudent <= 50)
						{
							string str = { Year };
							string yearStudent = { Year[0],Year[1],Year[2],Year[3] };

							fstream file;
							string filename = "database//HCMUS//" + Year + "//class_info.csv";
							int count = CheckRowInFile(filename);
							file.open("database//HCMUS//" + Year + "//class_info.csv", ios::app);
							file << endl << count + 1 << "," << name << "," << NameMajor << "," << numberStudent << "," << yearStudent;
							file.close();

							string FileName = "database//HCMUS//" + Year + "//" + name + csv_tail;
							fstream f1;
							f1.open(FileName, ios::out);
							f1 << "No" << "," << "ID" << "," << "Name" << "," << "Birth" << "," << "Sex" << "," << "IDSocial";
							f1.close();

							gotoxy(43, 23);
							cout << "CREATE CLASS SUCCESSFUL!!!" << endl;
							CreateClassInSemester(Year, name);
							Sleep(1000);
						}
						else
						{
							gotoxy(43, 21);
							cout << "Max Number Of Student is 50! Try again" << endl;
							Sleep(1000);
						}
					}
				}
			}
			else
			{
				gotoxy(43, 17);
				cout << "Name class is malformed!! Try again" << endl;
				Sleep(1000);
			}
		}
		else
		{
			gotoxy(43, 17);
			cout << "Name class is malformed!! Try again" << endl;
			Sleep(1000);
		}
	}
}



void drawASCIIMenuView()
{
	textBgColor(0, 15);
	DrawTextFile("_assets/class.txt", 38, 4);
	
}

void setRandom(string CheckNameClass, string CheckSTTClass, int& IDSt, int MasoNam) {
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
	if (CheckNameClass == "CLC")
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
	if (CheckNameClass == "VP")
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
}

void ImportRandom(string& YearCourse, string& Class)
{
	fstream ofs, ifs;
	string NameClass = "database//HCMUS//" + YearCourse + "//" + Class + csv_tail;
	ofs.open(NameClass, ios::app);
	ifs.open("database//InforNewStudent.csv", ios::in);
	string  NameSt, BirthSt, SexSt, IdSocialSt;
	int count = CheckRowInFile(NameClass);
	int IDSt = 0;
	string CheckYear = { YearCourse };
	string CheckNameYear = { CheckYear[2] , CheckYear[3] };
	int MasoNam;
	MasoNam = atoi(CheckNameYear.c_str()) * 1000000;
	string str = { Class };
	string CheckNameClass = { str[2] , str[3] , str[4] };
	string CheckSTTClass = { str[5] };
	
	setRandom(CheckNameClass, CheckSTTClass, IDSt, MasoNam);

	string NumberOfStudent;
	fstream file2;
	file2.open("database//HCMUS//" + YearCourse + "//class_info.csv", ios::in);
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
	int countFile = CheckRowInFile("database//InforNewStudent.csv");
	if (countFile < CheckRowInFile("database//InforNewStudent.csv"))
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
			finput.open("database//login_info.csv", ios::app);
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
		f1.open("database//InforNewStudent.csv", ios::in);

		while (!f1.eof())
		{
			for (int i = 0; i <= countFile; i++)
			{
				getline(f1, arr[i]);
			}
		}
		f1.close();
		fstream f2;
		f2.open("database//InforNewStudent.csv", ios::out);
		for (int i = CheckNumberOfStudent; i < countFile; i++)
		{
			f2 << arr[i] << endl;
		}
		f2.close();
	}
	string CheckSe = CheckSem();
	fstream F, FILE;
	string S = "database//HCMUS//" + YearCourse + "//Semester" + CheckSe + "//Class//" + Class + csv_tail;
	F.open(S, ios::app);
	int countF = CheckRowInFile(S);
	string SS = "database//HCMUS//" + YearCourse + "//" + Class + csv_tail;
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
	textBgColor(0, 19);
	drawRectangle(35, 12, 60, 12, 19);
	fstream fs;
	fs.open("database//year-semester.csv", ios::in);
	string tempYear;
	string tempSemester;
	while (!fs.eof())
	{
		getline(fs, tempYear, ',');
		getline(fs, tempSemester);
		Year = tempYear;
	}
	{
		textBgColor(0, 19);
		gotoxy(43, 13);
		cout << "Enter Name Abbreviations Of Class(CTT,CLC,VP,SHH): ";
		drawRectangle(43, 14, 45, 1, 15);
		gotoxy(43, 14);
		getline(cin, name);

		if (name == "CTT" || name == "CLC"
			|| name == "VP" || name == "SHH")
		{
			fstream file1;
			bool check = true;
			file1.open("database//HCMUS//" + Year + "//class_info.csv", ios::in);
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
				textBgColor(0, 19);
				gotoxy(43, 15);
				cout << "Enter Name Of Major: ";
				drawRectangle(43, 16, 45, 1, 15);
				gotoxy(43, 16);
				getline(cin, NameMajor);
				int numberStudent;
				textBgColor(0, 19);
				gotoxy(43, 17);
				cout << "Enter Number Of Student(Max=50): ";
				drawRectangle(43, 18, 45, 1, 15);
				gotoxy(43, 18);
				cin >> numberStudent;
				if (numberStudent <= 50)
				{
					int NumberOfClass;
					textBgColor(0, 19);
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
						string filename = "database//HCMUS//" + Year + "//class_info.csv";
						string CheckYear = { Year[2], Year[3] };
						for (int i = 1; i <= NumberOfClass; i++)
						{
							string s = to_string(i);
							string NameClasses = CheckYear + name + s;
							string FileName = "database//HCMUS//" + Year + "//" + NameClasses + csv_tail;
							fstream f1;
							f1.open(FileName, ios::out);
							f1 << "No" << "," << "ID" << "," << "Name" << "," << "Birth" << "," << "Sex" << "," << "IDSocial";;
							f1.close();
							int count = CheckRowInFile(filename);
							file.open("database//HCMUS//" + Year + "//class_info.csv", ios::app);
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
					cout << "Max Number Of Student is 50! Try Again!!!" << endl;
					Sleep(1000);
				}


			}
		}
		else
		{
			gotoxy(43, 17);
			cout << "Name class is malformed!! Try again" << endl;
			Sleep(1000);
		}
	}
}
int RunMenuCreateClass()
{
	char ch;
	int choice;
	while (true)
	{
		
		showPointer();
		system("cls");
		gotoxy(40, 12);
		string MenuView[] = { "1. Create 1 Class","2. Create Auto Classes And Import Info","3. Exit" };
		drawMenu(MenuView, 3, 47, 12, 1, &drawASCIIMenuView);
		choice = Select(3, MenuView, 47, 12, 1);
		switch (choice)
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

