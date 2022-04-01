#include "Staff.h"

void CopyContentFileToFile(string src_path, string des_path)
{
    fstream fileSource, fileDestination;
    fileSource.open(src_path, ios::in);
    fileDestination.open(des_path, ios::out);
    if (!fileSource.is_open()) return;
    string data;
    getline(fileSource, data);
    fileDestination << data;
    while (!fileSource.eof()) {
        getline(fileSource, data);
        fileDestination << endl << data;
    }
    fileSource.close();
    fileDestination.close();
}

void createFolder(string namefolder) {
    const char* NameFolder = namefolder.c_str();
    int check = _mkdir(NameFolder);
    if (check) {
        cout << "Could not create folder" << endl;
        exit(1);
    }
    return;
}

bool IsPathExist(const std::string& s)
{
    struct stat buffer;
    return (stat(s.c_str(), &buffer) == 0);
}

void DisplayYearSemester(string& Year, string& Semester)
{
    fstream fi;
    string semester;
    fi.open("database/year-semester.csv", ios::in);
    getline(fi, semester);
    while (!fi.eof()) {
        getline(fi, semester);
    }
    Year = semester.substr(0, 9);
    Semester = "Semester" + semester.substr(10, 1);
}

string CheckSem() {
	fstream classx;
	classx.open("_assets//year-semester.csv");
	string YearTem, SemTem;
	string CheckSem;
	while (!classx.eof())
	{
		getline(classx, YearTem, ',');
		classx >> SemTem;
		CheckSem = SemTem;
	}
	classx.close();
	return CheckSem;
}

void determineYearSemesterNow(string& Year, string& semester) {
    fstream file1;
    string data1;
    file1.open("_assets/year-semester.csv", ios::in);
    getline(file1, data1);
    while (!file1.eof()) {
        getline(file1, data1);
    }
    Year = data1.substr(0, 9);
    semester = "Semester" + data1.substr(10, 1);
}

int insertSchoolYear(string& SchoolYear) {
    int x = ReturnX(), y = ReturnY();
    char word;
    showPointer();
    do {
        word = _getch();
        if (word == 8) {
            if (SchoolYear.size() > 0) {
                SchoolYear.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        if (word == 27) {
            return 0;
        }
        else if (((word >= 48 && word <= 57) || word == 45) && SchoolYear.size() < 9) {
            cout << word;
            SchoolYear.push_back(word);
        }

    } while (word != 13 || SchoolYear.size() < 9);
    return 1;
}

void addSchoolYear(SchoolYear& Y) {
    SchoolYear schoolyear;
    char ch;
    system("cls");
    textBgColor(13, 15);

    while (true) {
        textBgColor(0, 11);
        drawRectangle(35, 8, 70, 7, 11);
        schoolyear.year = "";
        printtext("Enter school year (Ex:2020-2021,..) : ", 40, 10);
        drawRectangle(40, 11, 50, 1, 15);

        while (true) {
            showPointer();
            textBgColor(0, 15);
            gotoxy(40, 11);
            schoolyear.year = "";
            if (insertSchoolYear(schoolyear.year) == 0) return;
            string a, b;
            for (int i = 0; i < 4; i++) a.push_back(schoolyear.year[i]);
            for (int i = 5; i < 9; i++) b.push_back(schoolyear.year[i]);
            if (!(stoi(a, 0, 10) >= stoi(b, 0, 10) || schoolyear.year[4] != 45 || (stoi(a, 0, 10) < 1000 || stoi(a, 0, 10) > 9999) || (stoi(b, 0, 10) < 1000 || stoi(b, 0, 10) > 9999)))
                break;
            else {
                textBgColor(4, 11);
                printtext("Error: Format YYYY-YYYY", 40, 13);
                printtext("ENTER to try again", 40, 14);
                hidePointer();
                ch = _getch();
                drawRectangle(40, 11, 50, 1, 15);
                drawRectangle(40, 13, 60, 1, 11);
                drawRectangle(40, 14, 60, 1, 11);
                showPointer();
            }
        }

        fstream file1, file2;
        bool check = true;
        file1.open("_assets//year-semester.csv", ios::in);
        file2.open("_assets//year-semester.csv", ios::in);

        string row, column;
        getline(file1, row);
        getline(file2, column);
        while (!file1.eof()) {
            getline(file2, column, ',');
            if (column.compare(schoolyear.year) == 0) {
                textBgColor(4, 11);
                printtext("SCHOOL YEAR EXIST ! PRESS ENTER TO TRY AGAIN", 40, 14);
                hidePointer();
                ch = _getch();
                drawRectangle(40, 11, 50, 1, 15);
                drawRectangle(40, 14, 60, 1, 11);
                showPointer();
                check = false;
                break;
            }
            getline(file1, row);
            getline(file2, column);
        }
        if (check == true) break;
    }

    string nameFolder = "_assets//SchoolYear//" + schoolyear.year;
    createFolder(nameFolder);

    fstream file;
    string data;
    file.open("_assets//year-semester.csv", ios::app);
    file << endl << schoolyear.year << ",0";
    file.close();


    file.open("_assets/SchoolYear/" + Y.year + "/class_info.csv", ios::in);
    getline(file, data);
    while (!file.eof()) {
        getline(file, data, ',');
        getline(file, data, ',');
        string source = "_assets/SchoolYear/" + Y.year + "/" + data + ".csv", destination = "_assets/SchoolYear/" + schoolyear.year + "/" + data + ".csv";
        CopyContentFileToFile(source, destination);
        getline(file, data);
    }
    CopyContentFileToFile("_assets/SchoolYear/" + Y.year + "/staff.csv", "_assets/SchoolYear/" + schoolyear.year + "/staff.csv");
    CopyContentFileToFile("_assets/SchoolYear/" + Y.year + "/class_info.csv", "_assets/SchoolYear/" + schoolyear.year + "/class_info.csv");
    Y.year = schoolyear.year;
    Y.semester.Name = "Semester0";
    hidePointer();
    textBgColor(4, 11);
    printtext("CREATE SCHOOL YEAR SUCCESSFUL,PRESS ENTER TO BACK TO MENU !!!", 40, 14);
    ch = _getch();
    textBgColor(0, 15);
}


