#include "Staff.h"

void deleteFile(string filename) {
    char* a = new char[filename.size() + 1];
    strcpy(a, filename.c_str());
    a[filename.size()] = '\0';
    remove(a);
}

void renameFile(string oldName, string newName) {
    char* a = new char[oldName.size() + 1];
    strcpy(a, oldName.c_str());
    a[oldName.size()] = '\0';

    char* b = new char[newName.size() + 1];
    strcpy(b, newName.c_str());
    b[newName.size()] = '\0';

    rename(a, b);
}

void deleteCourse(string filename, string courseName, int currentLine, string year, string semester) {
    fstream file_be, file_af;
    string newdata, line;
    file_be.open(filename, ios::in);
    file_af.open("_assets//SchoolYear//" + year + "//" + semester + "//course_info_new.csv", ios::app);
    getline(file_be, line);
    file_af << line;
    int i = 2;
    while (!file_be.eof()) {
        if (i == currentLine) {
            getline(file_be, line);
        }
        else {
            getline(file_be, line);
            file_af << endl << line;
        }
        i++;
    }

    char* a = new char[filename.size() + 1];
    strcpy(a, filename.c_str());
    a[filename.size()] = '\0';
    string filename_new = "_assets/SchoolYear/" + year + "/" + semester + "/course_info_new.csv";
    char* b = new char[filename_new.size() + 1];
    strcpy(b, filename_new.c_str());
    b[filename_new.size()] = '\0';
    file_be.close();
    file_af.close();
    remove(a);
    rename(b, a);

    //xoa trong folder course
    deleteFile("_assets/SchoolYear/" + year + "/" + semester + "/Course/" + courseName + ".csv");

    //xoa trong folder score
    deleteFile("_assets/SchoolYear/" + year + "/" + semester + "/Course/score/" + courseName + ".csv");

    //Xoa trong folder class
    fstream file;
    file.open("_assets/SchoolYear/" + year + "/class_info.csv", ios::in);
    if (!file.is_open()) {
        return;
    }
    string info;
    getline(file, info);
    while (!file.eof()) {
        getline(file, info);
        info = info.substr(info.find(",") + 1, info.find(",", info.find(",") + 1) - info.find(",") - 1);
        fstream fileClass, file_new;
        fileClass.open("_assets/SchoolYear/" + year + "/" + semester + "/Class/" + info + ".csv", ios::in);
        file_new.open("_assets/SchoolYear/" + year + "/" + semester + "/Class/" + info + "_new.csv", ios::out);
        if (!fileClass.is_open() || !file_new.is_open()) continue;
        string line;
        int i = 1;
        while (!fileClass.eof()) {
            getline(fileClass, line);
            if (line.find("," + courseName) != -1) {
                line.erase(line.find("," + courseName), courseName.size() + 1);
            }
            if (i == 1) {
                file_new << line;
                i++;
            }
            else file_new << endl << line;
        }
        fileClass.close();
        file_new.close();
        deleteFile("_assets/SchoolYear/" + year + "/" + semester + "/Class/" + info + ".csv");
        renameFile("_assets/SchoolYear/" + year + "/" + semester + "/Class/" + info + "_new.csv", "_assets/SchoolYear/" + year + "/" + semester + "/Class/" + info + ".csv");
    }
    file.close();
}

void moveUp(string filename, int& currentLine, int columnNum, int indexB[], int y, string column[], int lineInConsole, int width, int x) {
    getLineInfo(filename, currentLine + 1, column, columnNum);
    drawRectangle(x, y + lineInConsole + 1, width, 1, 11);
    textBgColor(0, 11);
    for (int i = 0; i < columnNum; i++) {
        printtext(column[i], indexB[i], y + lineInConsole + 1);
    }

    getLineInfo(filename, currentLine, column, columnNum);
    drawRectangle(x, y + lineInConsole, width, 1, 14);
    textBgColor(0, 14);
    for (int i = 0; i < columnNum; i++) {
        printtext(column[i], indexB[i], y + lineInConsole);
    }
}

void moveDown(string filename, int& currentLine, int columnNum, int indexB[], int y, string column[], int lineInConsole, int width, int x) {

    getLineInfo(filename, currentLine - 1, column, columnNum);
    drawRectangle(x, y - 1 + lineInConsole, width, 1, 11);
    textBgColor(0, 11);
    for (int i = 0; i < columnNum; i++) {
        printtext(column[i], indexB[i], y + lineInConsole - 1);
    }
    getLineInfo(filename, currentLine, column, columnNum);
    drawRectangle(x, y + lineInConsole, width, 1, 14);
    textBgColor(0, 14);
    for (int i = 0; i < columnNum; i++) {
        printtext(column[i], indexB[i], y + lineInConsole);
    }
}

int editCourse(User A, string& year, string& semester) {
    int checkOut = -1;
    do {
        char ch;
        int line = countLine("_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv");
        int currentLine = 2;
        int y = 11;
        string column[8];
        int lineInConsole = 1;
        int a[8] = { 2,13,32,55,76,91,98,108 };
        int b[8] = { 1,9,32,63,79,91,101,111 };
        getLineInfo("_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv", currentLine, column, 8);
        drawRectangle(1, y + lineInConsole, 110, 1, 14);
        textBgColor(0, 14);
        for (int i = 0; i < 8; i++)
            printtext(column[i], b[i], y + lineInConsole);
        do {
            hidePointer();
            ch = _getch();
            //[ESC]
            if (ch == 27) {
                textBgColor(0, 15);
                checkOut = 1;
                break;
            }
            else {
                if (ch == 72 && currentLine > 2) //up
                {
                    currentLine--;
                    lineInConsole--;
                    if (lineInConsole + y <= 11) {
                        lineInConsole = 12;
                        drawRectangle(0, 10, 120, 15, 15);
                        drawRectangle(0, 10, 120, 15, 11);
                        drawList(8, "_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv", y, a, b, line, currentLine - 11);
                        getLineInfo("_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv", currentLine, column, 8);
                        drawRectangle(1, y + lineInConsole, 110, 1, 14);
                        textBgColor(0, 14);
                        for (int i = 0; i < 8; i++) {
                            printtext(column[i], b[i], y + lineInConsole);
                        }
                    }
                    else
                        moveUp("_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv", currentLine, 8, b, y, column, lineInConsole, 110, 1);

                }
                if (ch == 80 && currentLine < line) //down
                {
                    currentLine++;
                    lineInConsole++;
                    if (lineInConsole + y > 23) {
                        lineInConsole = 1;
                        drawRectangle(0, 10, 120, 15, 15);
                        drawRectangle(0, 10, 120, 15, 11);
                        drawList(8, "_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv", y, a, b, line, currentLine);
                        getLineInfo("_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv", currentLine, column, 8);
                        drawRectangle(1, y + lineInConsole, 110, 1, 14);
                        textBgColor(0, 14);
                        for (int i = 0; i < 8; i++) {
                            printtext(column[i], b[i], y + lineInConsole);
                        }
                    }
                    else
                        moveDown("_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv", currentLine, 8, b, y, column, lineInConsole, 110, 1);
                }
                if (ch == 13) {
                    //printtext();
                    editInforCourse(y + lineInConsole, currentLine, column, year, semester);
                    drawRectangle(1, y + lineInConsole, 110, 1, 14);
                    textBgColor(0, 14);
                    for (int i = 0; i < 8; i++)
                        printtext(column[i], b[i], y + lineInConsole);
                }

                if (ch == 'c') {
                    SchoolYear s;
                    change_Year_Semester(s);
                    year = s.year;
                    semester = s.semester.Name;
                    checkOut = 0;
                    break;
                    //editCourse(A, s.year, s.semester.Name);
                }

                if (ch == 'x') {
                    deleteCourse("_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv", column[0], currentLine, year, semester);
                    string filename = "_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv";
                    //drawList(8, filename , y, a, b, line,currentLine-lineInConsole+1);
                    if (currentLine == line) {
                        currentLine = line - 1;
                        if (lineInConsole == 1) lineInConsole = 12;
                        else lineInConsole--;
                    }
                    line--;

                    drawRectangle(0, 10, 120, 15, 11);
                    if (line == 1) {
                        textBgColor(4, 15);
                        printtext("THERE ISN'T ANY COURSE EXIST, PRESS ENTER TO BACK TO MENU.", 30, 14);
                        ch = _getch();
                        textBgColor(0, 15);
                        checkOut = 1;
                        break;
                    }
                    drawList(8, filename, y, a, b, line, currentLine - lineInConsole + 1);
                    drawRectangle(1, y + lineInConsole, 110, 1, 14);
                    textBgColor(0, 14);
                    getLineInfo(filename, currentLine, column, 8);
                    for (int i = 0; i < 8; i++)
                        printtext(column[i], b[i], y + lineInConsole);
                }
            }
        } while (true);
    } while (checkOut == -1);
    return checkOut;
}

void getLineInfo(string filename, int line, string column[], int columnNum) {
    if (line > countLine(filename)) cout << "Not exist line";
    int numLine = countLine(filename);
    fstream file;
    string data;
    file.open(filename, ios::in);
    for (int i = 1; i <= numLine; i++) {
        if (i == line) {
            for (int j = 0; j < columnNum; j++) {
                if (j != columnNum - 1) {
                    getline(file, data, ',');
                    column[j] = data;
                }
                else {
                    getline(file, data);
                    column[j] = data;
                }
            }
            break;
        }
        else {
            getline(file, data);
        }
    }
}

int insertNum(int& n) {
    char c;
    string num = "";
    do {
        showPointer();
        c = _getch();
        if (c == 8) {
            if (num.size() > 0) {
                num.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        else if (c >= 48 && c <= 57) {
            cout << c;
            num.push_back(c);
        }
        if (c == 27) {
            return 0;
        }
        if (c == 13) {
            if (num.size() >= 1) {
                break;
            }
        }
    } while (true);
    n = stoi(num, 0, 10);
    return 1;
}

int checkDate(string Date) {
    string dd, mm, yyyy;
    dd.push_back(Date[0]);
    dd.push_back(Date[1]);
    mm.push_back(Date[3]);
    mm.push_back(Date[4]);
    yyyy.push_back(Date[6]);
    yyyy.push_back(Date[7]);
    yyyy.push_back(Date[8]);
    yyyy.push_back(Date[9]);
    if (Date.size() < 10 || Date.find('/') != 2 || Date.find('/', 3) != 5 || (Date[2] != 47 || Date[5] != 47) || (stoi(dd, 0, 10) < 1 || stoi(dd, 0, 10) > 31) || (stoi(mm, 0, 10) < 1 || stoi(mm, 0, 10) > 12) || (stoi(yyyy, 0, 10) < 1000 || stoi(yyyy, 0, 10) > 9999))
        return 0;
    return 1;
}

int insertNameSemester(string& name) {
    char word;
    do {
        showPointer();
        word = _getch();
        if (word == 8) {
            if (name.size() > 0) {
                name.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        if (word == 27) {
            return 0;
        }
        else if (word >= 49 && word <= 51 && name.size() < 1) {
            cout << word;
            name.push_back(word);
        }
        if (word == 13) {
            if (name.size() == 1) break;
        }
    } while (true);
    return 1;
}

int insertDate(string& Date) {
    int x = ReturnX(), y = ReturnY();
    char word;
    showPointer();
    do {
        word = _getch();
        if (word == 8) {
            if (Date.size() > 0) {
                Date.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        else if (word >= 47 && word <= 57 && Date.size() < 10) {
            cout << word;
            Date.push_back(word);
        }
        if (word == 27) {
            return 0;
        }
    } while (word != 13 || Date.size() < 10);
    return 1;
}

void UpDatefileCSV(Semester semester) {
    fstream file_old1, file_old2, file_new;
    string data1, data2;
    file_old1.open("_assets//year-semester.csv", ios::in);
    file_old2.open("_assets//year-semester.csv", ios::in);
    file_new.open("_assets//year_semester_new.csv", ios::app);
    file_new << "Năm,số kì đã học ";
    getline(file_old2, data2);
    getline(file_old1, data1);
    data1 = data2 = "";
    while (!file_old2.eof()) {
        getline(file_old2, data2);
        while (!file_old1.eof()) {
            getline(file_old1, data1, ',');
            if (data1.compare(semester.schoolyear) == 0) {
                file_new << endl << data1;
                getline(file_old1, data1);
                int a = stoi(data1, 0, 10);
                a++;
                file_new << "," << to_string(a);
            }
            else file_new << endl << data2;
            getline(file_old1, data1);
            break;
        }
    }
    file_old1.close();
    file_old2.close();
    file_new.close();
    remove("_assets//year-semester.csv");
    rename("_assets//year_semester_new.csv", "_assets//year-semester.csv");
}

void UpDatefileInfo(Semester semester) {
    fstream file;
    file.open("_assets//SchoolYear//" + semester.schoolyear + "//Semester" + semester.Name + "//SemesterInfo.txt", ios::app);
    file << "Semester: " << semester.Name;
    file << endl << "Start Date: " << semester.date_star;
    file << endl << "End Date: " << semester.date_end;
    file.close();
}

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

void addSemester(string& yearNow, string& semesterNow) {
    char ch;
    Semester semester;
    system("cls");
    textBgColor(13, 15);
        
    textBgColor(0, 11);
    drawRectangle(25, 8, 80, 12, 11);
    printtext("Enter semester (1,2 or 3):", 35, 10);
    printtext("Enter school year of the semester (Ex:2020-2021,...):", 35, 12);
    printtext("Enter start date (dd/mm/yyyy):", 35, 14);
    printtext("Enter end date (dd/mm/yyyy):", 35, 16);
    drawRectangle(35, 11, 35, 1, 15);
    drawRectangle(35, 13, 35, 1, 15);
    drawRectangle(35, 15, 35, 1, 15);
    drawRectangle(35, 17, 35, 1, 15);

    gotoxy(35, 11);
    if (insertNameSemester(semester.Name) == 0) return;

    do {
        gotoxy(35, 13);
        if (insertSchoolYear(semester.schoolyear) == 0) return;
        int check = checkSchoolYear(semester);
        if (check != 1) {
            hidePointer();
            textBgColor(4, 11);
            gotoxy(35, 19);
            if (check == 0)
                printtext("ERROR:SCHOOL YEAR MUST HAVE FORMAT LIKE YYYY-YYYY,PRESS ENTER TO TRY AGAIN", 30, 19);
            else if (check == -1)
                printtext("ERROR:SCHOOL YEAR WASN'T EXISTED, PRESS ENTER TO TRY AGAIN", 30, 19);
            else if (check == -2)
                printtext("ERROR:SEMESTER WAS EXISTED IN SCHOOL YEAR, PRESS ENTER TO TRY AGAIN", 30, 19);
            else if (check == -3)
                printtext("ERROR:SEMESTER ISN'T COME UP,PRESS ENTER TO TRY AGAIN", 30, 19);
            ch = _getch();
            drawRectangle(30, 19, 75, 1, 11);
            drawRectangle(35, 13, 10, 1, 15);
            textBgColor(0, 15);
            semester.schoolyear = "";
            showPointer();
        }
        else break;
    } while (true);

    do {
        gotoxy(35, 15);
        if (insertDate(semester.date_star) == 0) return;
        int check = checkDate(semester.date_star);
        if (check == 0) {
            textBgColor(4, 11);
            gotoxy(35, 18);
            hidePointer();
            cout << "ERROR: DATE MUST HAVE FORMAT LIKE DD/MM/YYYY (01/02/2020)";
            printtext("PRESS ENTER TO TRY AGAIN", 35, 19);
            ch = _getch();
            drawRectangle(30, 18, 70, 1, 11);
            drawRectangle(30, 19, 70, 1, 11);
            drawRectangle(35, 15, 10, 1, 15);
            textBgColor(0, 15);
            semester.date_star.clear();
            showPointer();
        }
        else break;
    } while (true);

    do {
        gotoxy(35, 17);
        if (insertDate(semester.date_end) == 0) return;
        int check = checkDate(semester.date_end);
        if (check == 0) {
            textBgColor(4, 11);
            gotoxy(35, 18);
            hidePointer();
            cout << "ERROR: DATE MUST HAVE FORMAT LIKE DD/MM/YYYY (01/02/2020)";
            printtext("PRESS ENTER TO TRY AGAIN", 35, 19);
            ch = _getch();
            drawRectangle(30, 18, 70, 1, 11);
            drawRectangle(30, 19, 70, 1, 11);
            drawRectangle(35, 17, 10, 1, 15);
            textBgColor(0, 15);
            semester.date_end.clear();
            showPointer();
        }
        else break;
    } while (true);

    semesterNow = semester.Name;
    createFolder("_assets//SchoolYear//" + semester.schoolyear + "//Semester" + semester.Name);
    createFolder("_assets//SchoolYear//" + semester.schoolyear + "//Semester" + semester.Name + "//Class");
    createFolder("_assets//SchoolYear//" + semester.schoolyear + "//Semester" + semester.Name + "//Course");
    createFolder("_assets//SchoolYear//" + semester.schoolyear + "//Semester" + semester.Name + "//Course//score");
    UpDatefileCSV(semester);
    UpDatefileInfo(semester);

    fstream file;
    file.open("_assets//SchoolYear//" + semester.schoolyear + "//Semester" + semester.Name + "//course_info.csv", ios::out);
    file << "ID,COURSE NAME,TEACHER NAME,NUMBER OF CREDITS,MAX STUDENT,DAY,SESSION1,SESSION2";
    file.close();

    fstream fileCourse;
    fileCourse.open("_assets//SchoolYear//" + semester.schoolyear + "//Semester" + semester.Name + "//RegistrationCourseSession.txt", ios::out);
    fileCourse << 0;
    fileCourse.close();

    fstream class_info;
    class_info.open("_assets//SchoolYear//" + semester.schoolyear + "/class_info.csv", ios::in);
    if (!class_info.is_open()) return;
    string line;
    getline(class_info, line);
    while (!class_info.eof()) {
        getline(class_info, line);
        string className = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);
        fstream fileClass, fileStudent;
        fileClass.open("_assets/SchoolYear/" + semester.schoolyear + "/Semester" + semester.Name + "/Class/" + className + ".csv", ios::out);
        fileStudent.open("_assets/SchoolYear/" + semester.schoolyear + "/" + className + ".csv", ios::in);
        string studentID;
        getline(fileStudent, studentID);
        int t = 1;
        while (!fileStudent.eof()) {
            getline(fileStudent, studentID);
            studentID = studentID.substr(studentID.find(",") + 1, studentID.find(",", studentID.find(",") + 1) - studentID.find(",") - 1);
            if (t == 1) {
                fileClass << studentID; t++;
            }
            else fileClass << endl << studentID;
        }
    }
    hidePointer();
    textBgColor(10, 11);
    printtext("CREATE SEMESTER SUCCESSFUL,PRESS ENTER BACK TO MENU !!!", 35, 19);
    ch = _getch();
    textBgColor(0, 15);
}

int checkSchoolYear(Semester semester) {
    string a, b;
    for (int i = 0; i < 4; i++) a.push_back(semester.schoolyear[i]);
    for (int i = 5; i < 9; i++) b.push_back(semester.schoolyear[i]);
    //Không thõa mãn định dạng nhập yyyy-yyyy
    if (stoi(a, 0, 10) >= stoi(b, 0, 10) || semester.schoolyear[4] != 45 || (stoi(a, 0, 10) < 1000 || stoi(a, 0, 10) > 9999) || (stoi(b, 0, 10) < 1000 || stoi(b, 0, 10) > 9999))
        return 0;

    //Không tồn tại School Year
    if (IsPathExist("_assets//SchoolYear//" + semester.schoolyear) == false) return -1;

    //Kiểm tra thử trong School Year đã nhập đã có tồn tại semester vừa nhập chưa
    fstream file2;
    file2.open("_assets//year-semester.csv", ios::in);
    int check = 1;
    string column;
    getline(file2, column);
    while (!file2.eof()) {
        getline(file2, column, ',');
        if (column.compare(semester.schoolyear) == 0) {
            getline(file2, column, '\n');
            if (stoi(column, 0, 10) >= stoi(semester.Name, 0, 10)) check = -2;
            else if (stoi(semester.Name, 0, 10) - stoi(column, 0, 10) > 1) check = -3;
            break;
        }
        getline(file2, column);
    }
    file2.close();
    return check;
}

void createRegistrationCourse() {
    system("cls");
    string DateStart, DateEnd;
    char ch;

    string year, semester;
    determineYearSemesterNow(year, semester);
    if (stoi(semester.substr(8, 1), 0, 10) == 0) {
        textBgColor(4, 15);
        printtext("YOU HAVEN'T CREATED SEMESTER YET, PRESS ENTER TO BACK TO MENU.", 40, 10);
        ch = _getch();
    }
    else {
        drawRectangle(30, 20, 50, 7, 11);
        textBgColor(0, 11);
        printtext("START DATE (DD/MM/YYYY):", 35, 21);
        printtext("END DATE (DD/MM/YYYY):", 35, 24);
        drawRectangle(35, 22, 40, 1, 15);
        drawRectangle(35, 25, 40, 1, 15);

        string filename = "_assets//SchoolYear//" + year + "//" + semester + "//RegistrationCourseSession.txt";
        do {
            gotoxy(35, 22);
            if (insertDate(DateStart) == 0) return;
            int check = checkDate(DateStart);
            if (check == 0) {
                textBgColor(4, 15);
                gotoxy(20, 28);
                hidePointer();
                cout << "ERROR: DATE MUST HAVE FORMAT LIKE DD/MM/YYYY (01/02/2020,..), PRESS ENTER TO TRY AGAIN";
                ch = _getch();
                drawRectangle(20, 28, 90, 1, 15);
                drawRectangle(35, 22, 40, 1, 15);
                textBgColor(0, 15);
                DateStart.clear();
                showPointer();
            }
            else break;
        } while (true);

        do {
            gotoxy(35, 25);
            if (insertDate(DateEnd) == 0) return;
            int check = checkDate(DateEnd);
            if (check == 0) {
                textBgColor(4, 15);
                gotoxy(20, 28);
                hidePointer();
                cout << "ERROR: DATE MUST HAVE FORMAT LIKE DD/MM/YYYY (01/02/2020,..), PRESS ENTER TO TRY AGAIN";
                ch = _getch();
                drawRectangle(20, 28, 90, 1, 15);
                drawRectangle(35, 25, 40, 1, 15);
                textBgColor(0, 15);
                DateEnd.clear();
                showPointer();
            }
            else break;
        } while (true);
        hidePointer();
        fstream file;
        file.open(filename, ios::out);
        file << 1;
        file << endl << "Date start: " << DateStart;
        file << endl << "Date end:" << DateEnd;
        file.close();
        textBgColor(9, 15);
        printtext("CREATE COURSE REGISTRATION SESSION SUCCESSFUL !!! ,PRESS ENTER TO BACK TO MENU", 20, 28);
        ch = _getch();
    }
    textBgColor(0, 15);
}


void addCourse() {
    system("cls");
    char ch;
    Course course;
    string Day[7] = { "MON","TUE","WED","THU","FRI","SAT" }, session[4] = { "S1","S2","S3","S4" };

    string year = "", semester = "";
    determineYearSemesterNow(year, semester);
    if (stoi(semester.substr(8, 1), 0, 10) == 0) {
        textBgColor(4, 15);
        printtext("YOU HAVEN'T CREATED SEMESTER YET, PRESS ENTER TO BACK TO MENU.", 40, 10);
        ch = _getch();
    }

    else {
        drawRectangle(25, 9, 70, 18, 11);
        printtext("COURSE ID: ", 30, 10);
        printtext("COURSE NAME: ", 30, 12);
        printtext("TEACHER NAME: ", 30, 14);
        printtext("NUMBER OF CREDITS: ", 30, 16);
        printtext("MAXIMUN OF STUDENT: ", 30, 18);
        printtext("DAY OF THE WEEK (MON / TUE / WED / THU / FRI / SAT): ", 30, 20);
        printtext("SESSION: S1 (7:30), S2 (9:30), S3 (13:30), S4 (15:30) :", 30, 22);

        drawRectangle(30, 11, 50, 1, 15);
        drawRectangle(30, 13, 50, 1, 15);
        drawRectangle(30, 15, 50, 1, 15);
        drawRectangle(30, 17, 50, 1, 15);
        drawRectangle(30, 19, 50, 1, 15);
        drawRectangle(30, 21, 50, 1, 15);
        drawRectangle(30, 23, 50, 1, 15);
        drawRectangle(30, 24, 50, 1, 15);

        do
        {
            gotoxy(30, 11);
            if (insertString(course.ID_course, 15) == 0) return;
            if (countLine("_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv") == 1) break;
            fstream file;
            string line;
            file.open("_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv", ios::in);
            getline(file, line);
            bool check = false;
            while (!file.eof()) {
                getline(file, line, ',');
                if (line.compare(course.ID_course) != 0) {
                    check = true; break;
                }
            }
            if (check == true) break;
            else {
                textBgColor(4, 15);
                hidePointer();
                printtext("ERROR: COURSE ALREADY EXISTS,PRESS ENTER TO TRY AGAIN.", 25, 27);
                ch = _getch();
                textBgColor(0, 15);
                drawRectangle(25, 27, 80, 1, 15);
                drawRectangle(30, 11, 50, 1, 15);
            }
        } while (true);

        showPointer();
        gotoxy(30, 13);
        if (insertString(course.name, 20) == 0) return;
        gotoxy(30, 15);
        if (insertString(course.teacher, 20) == 0) return;
        gotoxy(30, 17);
        if (insertNum(course.Num_of_creadit) == 0) return;
        gotoxy(30, 19);
        if (insertNum(course.Max_student) == 0) return;
        do {
            gotoxy(30, 21);
            showPointer();
            if (insertString(course.DayOfWeek, 15) == 0) return;
            bool check = false;
            for (int i = 0; i < 7; i++) {
                if (course.DayOfWeek.compare(Day[i]) == 0) {
                    check = true;
                    break;
                }
            }
            if (check == true) break;
            else {
                course.DayOfWeek = "";
                textBgColor(4, 15);
                hidePointer();
                printtext("ERROR: YOUR DAY MUST HAVE FORMAT LIKE (MON,TUE,..),PRESS ENTER TO TRY AGAIN.", 25, 27);
                ch = _getch();
                textBgColor(0, 15);
                drawRectangle(25, 27, 80, 1, 15);
                drawRectangle(30, 21, 50, 1, 15);
            }
        } while (true);

        do
        {
            gotoxy(30, 23);
            showPointer();
            if (insertString(course.session[0], 15) == 0) return;
            bool check = false;
            for (int i = 0; i < 4; i++) {
                if (course.session[0].compare(session[i]) == 0) {
                    check = true;
                    break;
                }
            }
            if (check == true) break;
            else {
                course.session[0] = "";
                textBgColor(4, 15);
                hidePointer();
                printtext("ERROR: YOUR SESSION MUST HAVE FORMAT LIKE (S1,S2,..),PRESS ENTER TO TRY AGAIN.", 25, 27);
                textBgColor(0, 15);
                ch = _getch();
                drawRectangle(25, 27, 80, 1, 15);
                drawRectangle(30, 23, 50, 1, 15);
            }
        } while (true);

        do
        {
            gotoxy(30, 24);
            showPointer();
            if (insertString(course.session[1], 15) == 0) return;
            int check = 0;
            for (int i = 0; i < 4; i++) {
                if (course.session[1].compare(session[i]) == 0) {
                    if (course.session[1].compare(course.session[0]) == 0)
                        check = -1;
                    else check = 1;
                    break;
                }
            }
            if (check == 1) break;
            else {
                course.session[1] = "";
                textBgColor(4, 15);
                hidePointer();
                if (check == 0)
                    printtext("ERROR: YOUR SESSION MUST HAVE FORMAT LIKE (S1,S2,..),PRESS ENTER TO TRY AGAIN.", 25, 27);
                else
                    printtext("ERROR: YOUR SESSION IS THE SAME AS LAST SESSION ,PRESS ENTER TO TRY AGAIN.", 25, 27);
                textBgColor(0, 15);
                ch = _getch();
                drawRectangle(25, 27, 80, 1, 15);
                drawRectangle(30, 24, 50, 1, 15);
            }
        } while (true);
        fstream file;
        file.open("_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv", ios::app);
        file << endl << course.ID_course << "," << course.name << "," << course.teacher << "," << course.Num_of_creadit << "," << course.Max_student << "," << course.DayOfWeek << "," << course.session[0] << "," << course.session[1];
        file.close();

        file.open("_assets/SchoolYear/" + year + "/" + semester + "/Course/" + course.ID_course + ".csv", ios::out);
        file << "ID STUDENT,NAME,BIRTHDAY,SEX,ID SOCIAL";
        file.close();
        printtext("CREATE COURSE SUCCESSFUL !!!, PRESS ENTER TO BACK TO MENU.", 25, 27);
        ch = _getch();
    }
    textBgColor(0, 15);
}

int countLine(string filename) {
    fstream file;
    string line;
    file.open(filename, ios::in);
    int count = 0;
    while (getline(file, line, '\n'))
        count++;
    file.close();
    return count;
}

void drawList(int columnNum, string filename, int y, int indexA[], int indexB[], int line, int flagLine) {
    if (line == 0 || columnNum == 0) return;
    string* datanew = new string[line];
    string* column = new string[columnNum];
    textBgColor(4, 11);

    getLineInfo(filename, 1, column, columnNum);
    for (int i = 0; i < columnNum; i++) {
        printtext(column[i], indexA[i], y);
    }
    textBgColor(0, 11);
    y++;
    int j = flagLine, h = 1;
    while (j <= line && h <= 12) {
        getLineInfo(filename, j, column, columnNum);
        for (int i = 0; i < columnNum; i++) {
            printtext(column[i], indexB[i], y);
        }
        y++; j++;
        h++;
    }
}


void listCourse(User A, string year, string semester) {

    char ch;
    if (stoi(semester.substr(8, 1), 0, 10) == 0) {
        textBgColor(4, 15);
        printtext("YOU HAVEN'T CREATED SEMESTER YET, PRESS ENTER TO BACK TO MENU.", 30, 14);
        ch = _getch();
        textBgColor(0, 15);
        return;
    }
    int checkOut = -1;
    do {
        hidePointer();
        system("cls");

        drawRectangle(97, 0, 22, 5, 11);
        textBgColor(4, 11);
        printtext("-[ESC]: BACK TO MENU", 97, 2);
        printtext("OR RETURN", 97, 3);

        drawRectangle(0, 0, 26, 5, 11);
        textBgColor(4, 11);
        printtext("-[x]: DELETE COURSE", 0, 0.5);
        printtext("-[ENTER]: EDIT COURSE", 0, 1.5);
        printtext("-USE UP,DOWN,LEFT,RIGHT", 0, 2.5);
        printtext("KEY TO MOVE IN EDIT STATUS", 0, 3.5);
        printtext("-[c]: CHANGE TIME", 0, 4.5);

        string filename = "_assets/SchoolYear/" + year + "/" + semester + "/course_info.csv";
        int lineNum = countLine(filename);
        if (lineNum == 1) {
            textBgColor(4, 15);
            printtext("THERE ISN'T ANY COURSE EXIST, PRESS ENTER TO BACK TO MENU.", 30, 14);
            ch = _getch();
            textBgColor(0, 15);
            break;
        }
        drawRectangle(0, 10, 120, 15, 11);
        int a[8] = { 2,13,32,55,76,91,98,108 };
        int b[8] = { 1,9,32,63,79,91,101,111 };
        drawList(8, filename, 11, a, b, lineNum, 2);
        hidePointer();
        checkOut = editCourse(A, year, semester);
        textBgColor(0, 15);
    } while (checkOut == -1 || checkOut == 0);
}
int insertString(string& data, int limit) {
    char ch;
    do
    {
        showPointer();
        ch = _getch();
        if (ch == 8) {
            if (data.size() > 0) {
                data.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        else if (ch == 32 && data.size() < limit) {
            data.push_back(ch);
            cout << " ";
        }
        else if (((ch >= 33 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || ch == 95) && data.size() < limit) {
            cout << ch;
            data.push_back(ch);
        }
        if (ch == 27) {
            return 0;
        }
        if (ch == 13) {
            if (data.size() > 1) {
                break;
            }
        }
    } while (true);
    return 1;
}

void addSchoolYear(SchoolYear& Y) {
    SchoolYear schoolyear;
    char ch;
    system("cls");
    textBgColor(13, 15);
    DrawTextFile("_assets\\menu_schoolyear.txt", 35, 2);
    
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
            //Không thõa mãn định dạng nhập yyyy-yyyy
            if (!(stoi(a, 0, 10) >= stoi(b, 0, 10) || schoolyear.year[4] != 45 || (stoi(a, 0, 10) < 1000 || stoi(a, 0, 10) > 9999) || (stoi(b, 0, 10) < 1000 || stoi(b, 0, 10) > 9999)))
                break;
            else {
                textBgColor(4, 11);
                printtext("ERROR:SCHOOL YEAR MUST HAVE FORMAT LIKE YYYY-YYYY", 40, 13);
                printtext("PRESS ENTER TO TRY AGAIN", 40, 14);
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
        file1.open("database//year-semester.csv", ios::in);
        file2.open("database//year-semester.csv", ios::in);

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

    string nameFolder = "database//SchoolYear//" + schoolyear.year;
    createFolder(nameFolder);

    fstream file;
    string data;
    file.open("database//year-semester.csv", ios::app);
    file << endl << schoolyear.year << ",0";
    file.close();


    file.open("database/SchoolYear/" + Y.year + "/class_info.csv", ios::in);
    getline(file, data);
    while (!file.eof()) {
        getline(file, data, ',');
        getline(file, data, ',');
        string source = "database/SchoolYear/" + Y.year + "/" + data + ".csv", destination = "database/SchoolYear/" + schoolyear.year + "/" + data + ".csv";
        CopyContentFileToFile(source, destination);
        getline(file, data);
    }
    CopyContentFileToFile("database/SchoolYear/" + Y.year + "/staff.csv", "database/SchoolYear/" + schoolyear.year + "/staff.csv");
    CopyContentFileToFile("database/SchoolYear/" + Y.year + "/class_info.csv", "file_save/SchoolYear/" + schoolyear.year + "/class_info.csv");
    Y.year = schoolyear.year;
    Y.semester.Name = "Semester0";
    hidePointer();
    textBgColor(4, 11);
    printtext("CREATE SCHOOL YEAR SUCCESSFUL,PRESS ENTER TO BACK TO MENU !!!", 40, 14);
    ch = _getch();
    textBgColor(0, 15);
}