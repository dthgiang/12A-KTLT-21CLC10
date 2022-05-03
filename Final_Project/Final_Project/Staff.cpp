#include "Staff.h"
#include "System_Function.h"

// cái rename nó bị warning á, m gán giá trị rename thành 1 biến thử xem chạy dc ko
void updateCourseFile(int currentColumn, int currentLine, string column[], string year, string semester) {
    fstream be, af;
    string filename = "database//HCMUS//" + year + "//" + semester + "//course_info.csv";
    string newdata, line;
    for (int i = 0; i < 8; i++) {
        if (i != 7) {
            newdata = newdata + column[i] + ",";
        }
        else newdata = newdata + column[i];
    }
    af.open("database//HCMUS//" + year + "//" + semester + "//course_info_new.csv", ios::app);
    be.open(filename, ios::in);
    getline(be, line);
    af << line;
    int i = 2;
    while (!be.eof()) {
        if (i == currentLine) {
            af << endl << newdata;
            getline(be, line);
        }
        else {
            getline(be, line);
            af << endl << line;
        }
        i++;
    }
    char* a = new char[filename.size() + 1];
    strcpy(a, filename.c_str());
    a[filename.size()] = '\0';
    string filename_new = "database/HCMUS/" + year + "/" + semester + "/course_info_new.csv";
    char* b = new char[filename_new.size() + 1];
    strcpy(b, filename_new.c_str());
    b[filename_new.size()] = '\0';
    remove(a);rename(b, a);
    be.close();
    af.close();
}

int insertNum2(string& data, int limit) {
    char ch;
    do {
        ch = _getch();
        if (ch == 8) {
            if (data.size() > 0) {
                data.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        if (ch == 27) {
            return 0;
        }
        else if ((ch >= 48 && ch <= 57) && data.size() < limit) {
            cout << ch;
            data.push_back(ch);
        }
    } while (ch != 13);
    return 1;
}
int insertDay(string& data, int limit) {
    string Day[7] = { "MON","TUE","WED","THU","FRI","SAT" };
    char ch;
    bool check = false;
    do
    {
        ch = _getch();
        if (ch == 8) {
            if (data.size() > 0) {
                data.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        else if ((ch >= 65 && ch <= 90) && data.size() < limit) {
            cout << ch;
            data.push_back(ch);
        }
        if (ch == 27) {
            return 0;
        }
        for (int i = 0; i < 7; i++) {
            if (data.compare(Day[i]) == 0) { check = true; break; }
        }
    } while (ch != 13 || check == false);
    return 1;
}

int insertSession(string& data, int limit) {
    string session[4] = { "S1","S2","S3","S4" };
    char ch;
    bool check = false;
    do
    {
        ch = _getch();
        if (ch == 8) {
            if (data.size() > 0) {
                data.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        else if (((ch >= 65 && ch <= 90) || (ch >= 48 && ch <= 57)) && data.size() < limit) {
            cout << ch;
            data.push_back(ch);
        }
        if (ch == 27) {
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            if (data.compare(session[i]) == 0) { check = true; break; }
        }
    } while (ch != 13 || check == false);
    return 1;
}

void editInforCourse(int y, int currentLine, string column[], string year, string semester) {
    char ch;
    int currentColumn = 2, pos[8] = { 1,9,32,63,79,91,101,111 }, limit[8] = { 5,20,20,3,5,5,2,2 };
    drawRectangle(pos[currentColumn], y, 5, 1, 15);
    textBgColor(0, 15);
    printtext(column[2], pos[currentColumn], y);
    do
    {
        ch = _getch();
        //ESC
        if (ch == 27)
            break;
        //Left 
        if (ch == 75 && currentColumn > 2) {
            drawRectangle(pos[currentColumn], y, limit[currentColumn], 1, 14);
            textBgColor(0, 14);
            printtext(column[currentColumn], pos[currentColumn], y);

            currentColumn--;
            drawRectangle(pos[currentColumn], y, limit[currentColumn], 1, 15);
            textBgColor(0, 15);
            printtext(column[currentColumn], pos[currentColumn], y);
        }
        //Right
        if (ch == 77 && currentColumn < 7) {
            drawRectangle(pos[currentColumn], y, limit[currentColumn], 1, 14);
            textBgColor(0, 14);
            printtext(column[currentColumn], pos[currentColumn], y);

            currentColumn++;
            drawRectangle(pos[currentColumn], y, limit[currentColumn], 1, 15);
            textBgColor(0, 15);
            printtext(column[currentColumn], pos[currentColumn], y);
        }

        //[ENTER]
        if (ch == 13) {
            showPointer();
            textBgColor(0, 15);

            if (currentColumn == 2) {
                gotoxy(pos[currentColumn] + column[currentColumn].size(), y);
                insertString(column[2], limit[currentColumn]);
            }
            else if (currentColumn == 3) {
                gotoxy(pos[currentColumn] + column[currentColumn].size(), y);
                insertNum2(column[currentColumn], limit[currentColumn]);
            }
            else if (currentColumn == 4) {
                gotoxy(pos[currentColumn] + column[currentColumn].size(), y);
                insertNum2(column[currentColumn], limit[currentColumn]);
            }
            else if (currentColumn == 5) {
                gotoxy(pos[currentColumn] + column[currentColumn].size(), y);
                insertDay(column[currentColumn], limit[currentColumn]);
            }
            else {
                gotoxy(pos[currentColumn] + column[currentColumn].size(), y);
                insertSession(column[currentColumn], limit[currentColumn]);
            }
            hidePointer();
            updateCourseFile(currentColumn, currentLine, column, year, semester);
        }
    } while (true);
}

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
    fstream be, af;
    string newdata, line;
    be.open(filename, ios::in);
    af.open("database//HCMUS//" + year + "//" + semester + "//course_info_new.csv", ios::app);
    getline(be, line);
    af << line;
    int i = 2;
    while (!be.eof()) {
        if (i == currentLine) {
            getline(be, line);
        }
        else {
            getline(be, line);
            af << endl << line;
        }
        i++;
    }

    char* a = new char[filename.size() + 1];
    strcpy(a, filename.c_str());
    a[filename.size()] = '\0';
    string filename_new = "database/HCMUS/" + year + "/" + semester + "/course_info_new.csv";
    char* b = new char[filename_new.size() + 1];
    strcpy(b, filename_new.c_str());
    b[filename_new.size()] = '\0';
    be.close();
    af.close();
    remove(a);
    rename(b, a);

    //xoa trong folder course
    deleteFile("database/HCMUS/" + year + "/" + semester + "/Course/" + courseName + ".csv");

    //xoa trong folder score
    deleteFile("database/HCMUS/" + year + "/" + semester + "/Course/score/" + courseName + ".csv");

    //Xoa trong folder class
    fstream file;
    file.open("database/HCMUS/" + year + "/class_info.csv", ios::in);
    if (!file.is_open()) {
        return;
    }
    string info;
    getline(file, info);
    while (!file.eof()) {
        getline(file, info);
        info = info.substr(info.find(",") + 1, info.find(",", info.find(",") + 1) - info.find(",") - 1);
        fstream fileClass, fnew;
        fileClass.open("database/HCMUS/" + year + "/" + semester + "/Class/" + info + ".csv", ios::in);
        fnew.open("database/HCMUS/" + year + "/" + semester + "/Class/" + info + "_new.csv", ios::out);
        if (!fileClass.is_open() || !fnew.is_open()) continue;
        string line;
        int i = 1;
        while (!fileClass.eof()) {
            getline(fileClass, line);
            if (line.find("," + courseName) != -1) {
                line.erase(line.find("," + courseName), courseName.size() + 1);
            }
            if (i == 1) {
                fnew << line;
                i++;
            }
            else fnew << endl << line;
        }
        fileClass.close();
        fnew.close();
        deleteFile("database/HCMUS/" + year + "/" + semester + "/Class/" + info + ".csv");
        renameFile("database/HCMUS/" + year + "/" + semester + "/Class/" + info + "_new.csv", "database/HCMUS/" + year + "/" + semester + "/Class/" + info + ".csv");
    }
    file.close();
}



int editCourse(User A, string& year, string& semester) {
    int checkOut = -1;
    do {
        char ch;
        int line = countLine("database/HCMUS/" + year + "/" + semester + "/course_info.csv");
        int currentLine = 2;
        int y = 11;
        string column[8];
        int lineInConsole = 1;
        int a[8] = { 2,13,32,55,76,91,98,108 };
        int b[8] = { 1,9,32,63,79,91,101,111 };
        getLineInfoForStudent("database/HCMUS/" + year + "/" + semester + "/course_info.csv", currentLine, column, 8);
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
                        drawRectangle(0, 10, 120, 15, 19);
                        drawList(8, "database/HCMUS/" + year + "/" + semester + "/course_info.csv", y, a, b, line, currentLine - 11);
                        getLineInfoForStudent("database/HCMUS/" + year + "/" + semester + "/course_info.csv", currentLine, column, 8);
                        drawRectangle(1, y + lineInConsole, 110, 1, 14);
                        textBgColor(0, 14);
                        for (int i = 0; i < 8; i++) {
                            printtext(column[i], b[i], y + lineInConsole);
                        }
                    }
                    else
                        moveUp("database/HCMUS/" + year + "/" + semester + "/course_info.csv", currentLine, 8, b, y, column, lineInConsole, 110, 1);

                }
                if (ch == 80 && currentLine < line) //down
                {
                    currentLine++;
                    lineInConsole++;
                    if (lineInConsole + y > 23) {
                        lineInConsole = 1;
                        drawRectangle(0, 10, 120, 15, 15);
                        drawRectangle(0, 10, 120, 15, 19);
                        drawList(8, "database/HCMUS/" + year + "/" + semester + "/course_info.csv", y, a, b, line, currentLine);
                        getLineInfoForStudent("database/HCMUS/" + year + "/" + semester + "/course_info.csv", currentLine, column, 8);
                        drawRectangle(1, y + lineInConsole, 110, 1, 14);
                        textBgColor(0, 14);
                        for (int i = 0; i < 8; i++) {
                            printtext(column[i], b[i], y + lineInConsole);
                        }
                    }
                    else
                        moveDown("database/HCMUS/" + year + "/" + semester + "/course_info.csv", currentLine, 8, b, y, column, lineInConsole, 110, 1);
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
                    change_Sem(s);
                    year = s.year;
                    semester = s.semester.Name;
                    checkOut = 0;
                    break;
                    //editCourse(A, s.year, s.semester.Name);
                }

                if (ch == 'x') {
                    deleteCourse("database/HCMUS/" + year + "/" + semester + "/course_info.csv", column[0], currentLine, year, semester);
                    string filename = "database/HCMUS/" + year + "/" + semester + "/course_info.csv";
                    //drawList(8, filename , y, a, b, line,currentLine-lineInConsole+1);
                    if (currentLine == line) {
                        currentLine = line - 1;
                        if (lineInConsole == 1) lineInConsole = 12;
                        else lineInConsole--;
                    }
                    line--;

                    drawRectangle(0, 10, 120, 15, 19);
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
                    getLineInfoForStudent(filename, currentLine, column, 8);
                    for (int i = 0; i < 8; i++)
                        printtext(column[i], b[i], y + lineInConsole);
                }
            }
        } while (true);
    } while (checkOut == -1);
    return checkOut;
}

void getLineInfoForStudent(string filename, int line, string column[], int columnNum) {
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

void moveUp(string filename, int& currentLine, int columnNum, int indexB[], int y, string column[], int lineInConsole, int width, int x)
{
    getLineInfoForStudent(filename, currentLine + 1, column, columnNum);
    drawRectangle(x, y + lineInConsole + 1, width, 1, 19);
    textBgColor(0, 19);
    for (int i = 0; i < columnNum; i++) {
        printtext(column[i], indexB[i], y + lineInConsole + 1);
    }

    getLineInfoForStudent(filename, currentLine, column, columnNum);
    drawRectangle(x, y + lineInConsole, width, 1, 14);
    textBgColor(0, 14);
    for (int i = 0; i < columnNum; i++) {
        printtext(column[i], indexB[i], y + lineInConsole);
    }
}

void moveDown(string filename, int& currentLine, int columnNum, int indexB[], int y, string column[], int lineInConsole, int width, int x)
{
    getLineInfoForStudent(filename, currentLine - 1, column, columnNum);
    drawRectangle(x, y - 1 + lineInConsole, width, 1, 19);
    textBgColor(0, 19);
    for (int i = 0; i < columnNum; i++) {
        printtext(column[i], indexB[i], y + lineInConsole - 1);
    }
    getLineInfoForStudent(filename, currentLine, column, columnNum);
    drawRectangle(x, y + lineInConsole, width, 1, 14);
    textBgColor(0, 14);
    for (int i = 0; i < columnNum; i++) {
        printtext(column[i], indexB[i], y + lineInConsole);
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
    fstream old1, old2, fnew;
    string data1, data2;
    old1.open("database//year-semester.csv", ios::in);
    old2.open("database//year-semester.csv", ios::in);
    fnew.open("database//year_semester_new.csv", ios::app);
    fnew << "Năm,số kì đã học ";
    getline(old2, data2);
    getline(old1, data1);
    data1 = data2 = "";
    while (!old2.eof()) {
        getline(old2, data2);
        while (!old1.eof()) {
            getline(old1, data1, ',');
            if (data1.compare(semester.schoolyear) == 0) {
                fnew << endl << data1;
                getline(old1, data1);
                int a = stoi(data1, 0, 10);
                a++;
                fnew << "," << to_string(a);
            }
            else fnew << endl << data2;
            getline(old1, data1);
            break;
        }
    }
    old1.close();
    old2.close();
    fnew.close();
    remove("database//year-semester.csv");
    rename("database//year_semester_new.csv", "database//year-semester.csv");
}

void UpDatefileInfo(Semester semester) {
    fstream file;
    file.open("database//HCMUS//" + semester.schoolyear + "//Semester" + semester.Name + "//SemesterInfo.txt", ios::app);
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

void determineYearSemesterNow(string& Year, string& semester) {
    fstream file1;
    string data1;
    file1.open("database/year-semester.csv", ios::in);
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
        DrawTextFile("_assets/menu_schoolyear.txt", 20, 2);
 
        drawRectangle(20, 8, 76, 7, 11);
        schoolyear.year = "";
        printtext("Enter school year (Ex:2020-2021,..) : ", 35, 10);
        drawRectangle(35, 11, 50, 1, 15);

        while (true) {
            showPointer();
            textBgColor(0, 15);
            gotoxy(35, 11);
            schoolyear.year = "";
            if (insertSchoolYear(schoolyear.year) == 0) return;
            string a, b;
            for (int i = 0; i < 4; i++) a.push_back(schoolyear.year[i]);
            for (int i = 5; i < 9; i++) b.push_back(schoolyear.year[i]);
            if (!(stoi(a, 0, 10) >= stoi(b, 0, 10) || schoolyear.year[4] != 45 || (stoi(a, 0, 10) < 1000 || stoi(a, 0, 10) > 9999) || (stoi(b, 0, 10) < 1000 || stoi(b, 0, 10) > 9999)))
                break;
            else {
                textBgColor(4, 11);
                printtext("Error: Format YYYY-YYYY", 33, 13);
                printtext("ENTER to try again", 35, 14);
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
                printtext("SCHOOL YEAR EXIST ! PRESS ENTER TO TRY AGAIN", 35, 14);
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

    string nameFolder = "database//HCMUS//" + schoolyear.year;
    createFolder(nameFolder);

    fstream file;
    string data;
    file.open("database//year-semester.csv", ios::app);
    file << endl << schoolyear.year << ",0";
    file.close();


    file.open("database/HCMUS/" + Y.year + "/class_info.csv", ios::in);
    getline(file, data);
    while (!file.eof()) {
        getline(file, data, ',');
        getline(file, data, ',');
        string source = "database/HCMUS/" + Y.year + "/" + data + ".csv", destination = "database/HCMUS/" + schoolyear.year + "/" + data + ".csv";
        CopyContentFileToFile(source, destination);
        getline(file, data);
    }
    CopyContentFileToFile("database/HCMUS/" + Y.year + "/staff.csv", "database/HCMUS/" + schoolyear.year + "/staff.csv");
    CopyContentFileToFile("database/HCMUS/" + Y.year + "/class_info.csv", "database/HCMUS/" + schoolyear.year + "/class_info.csv");
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
    drawRectangle(3, 3, 115, 8, 19);
    textBgColor(15, 19);
    DrawTextFile("_assets\\create_semester.txt", 12, 3);
    textBgColor(0, 19);
    drawRectangle(22, 13, 80, 12, 19);
    printtext("Enter semester (1,2 or 3):", 35, 15);
    printtext("Enter school year of the semester (Ex:2020-2021,...):", 35, 17);
    printtext("Enter start date (dd/mm/yyyy):", 35, 19);
    printtext("Enter end date (dd/mm/yyyy):", 35, 21);
    drawRectangle(35, 16, 35, 1, 15);
    drawRectangle(35, 18, 35, 1, 15);
    drawRectangle(35, 20, 35, 1, 15);
    drawRectangle(35, 22, 35, 1, 15);
    gotoxy(35, 16);
    if (insertNameSemester(semester.Name) == 0) return;
    do {
        gotoxy(35, 18);
        if (insertSchoolYear(semester.schoolyear) == 0) return;
        int check = checkSchoolYear(semester);
        if (check != 1) {
            hidePointer();
            textBgColor(4, 19);
            gotoxy(35, 24);
            if (check == 0)
                printtext("ERROR:SCHOOL YEAR MUST HAVE FORMAT LIKE YYYY-YYYY,PRESS ENTER TO TRY AGAIN", 26, 24);
            else if (check == -1)
                printtext("ERROR:SCHOOL YEAR WASN'T EXISTED, PRESS ENTER TO TRY AGAIN", 26, 24);
            else if (check == -2)
                printtext("ERROR:SEMESTER WAS EXISTED IN SCHOOL YEAR, PRESS ENTER TO TRY AGAIN", 26, 24);
            else if (check == -3)
                printtext("ERROR:SEMESTER ISN'T COME UP,PRESS ENTER TO TRY AGAIN", 26, 24);
            ch = _getch();
            drawRectangle(25, 24, 75, 1, 19);
            drawRectangle(35, 18, 10, 1, 15);
            textBgColor(0, 15);
            semester.schoolyear = "";
            showPointer();
        }
        else break;
    } while (true);
    do {
        gotoxy(35, 20);
        if (insertDate(semester.date_star) == 0) return;
        int check = checkDate(semester.date_star);
        if (check == 0) {
            textBgColor(4, 19);
            gotoxy(35, 23);
            hidePointer();
            cout << "ERROR: DATE MUST HAVE FORMAT LIKE DD/MM/YYYY (01/02/2020)";
            printtext("PRESS ENTER TO TRY AGAIN", 35, 24);
            ch = _getch();
            drawRectangle(30, 23, 70, 1, 11);
            drawRectangle(30, 24, 70, 1, 11);
            drawRectangle(35, 20, 10, 1, 15);
            textBgColor(0, 15);
            semester.date_star.clear();
            showPointer();
        }
        else break;
    } while (true);
    do {
        gotoxy(35, 22);
        if (insertDate(semester.date_end) == 0) return;
        int check = checkDate(semester.date_end);
        if (check == 0) {
            textBgColor(4, 19);
            gotoxy(35, 23);
            hidePointer();
            cout << "ERROR: DATE MUST HAVE FORMAT LIKE DD/MM/YYYY (01/02/2020)";
            printtext("PRESS ENTER TO TRY AGAIN", 35, 24);
            ch = _getch();
            drawRectangle(30, 23, 70, 1, 11);
            drawRectangle(30, 24, 70, 1, 11);
            drawRectangle(35, 22, 10, 1, 15);
            textBgColor(0, 15);
            semester.date_end.clear();
            showPointer();
        }
        else break;
    } while (true);
    semesterNow = semester.Name;
    createFolder("database//HCMUS//" + semester.schoolyear + "//Semester" + semester.Name);
    createFolder("database//HCMUS//" + semester.schoolyear + "//Semester" + semester.Name + "//Class");
    createFolder("database//HCMUS//" + semester.schoolyear + "//Semester" + semester.Name + "//Course");
    createFolder("database//HCMUS//" + semester.schoolyear + "//Semester" + semester.Name + "//Course//score");
    UpDatefileCSV(semester);
    UpDatefileInfo(semester);
    fstream file;
    file.open("database//HCMUS//" + semester.schoolyear + "//Semester" + semester.Name + "//course_info.csv", ios::out);
    file << "ID,COURSE NAME,TEACHER NAME,NUMBER OF CREDITS,MAX STUDENT,DAY,SESSION1,SESSION2";
    file.close();
    fstream fileCourse;
    fileCourse.open("database//HCMUS//" + semester.schoolyear + "//Semester" + semester.Name + "//RegistrationCourseSession.txt", ios::out);
    fileCourse << 0;
    fileCourse.close();
    fstream class_info;
    class_info.open("database//HCMUS//" + semester.schoolyear + "/class_info.csv", ios::in);
    if (!class_info.is_open()) return;
    string line;
    getline(class_info, line);
    while (!class_info.eof()) {
        getline(class_info, line);
        string className = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);
        fstream fileClass, fileStudent;
        fileClass.open("database/HCMUS/" + semester.schoolyear + "/Semester" + semester.Name + "/Class/" + className + ".csv", ios::out);
        fileStudent.open("database/HCMUS/" + semester.schoolyear + "/" + className + ".csv", ios::in);
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
    if (stoi(a, 0, 10) >= stoi(b, 0, 10) || semester.schoolyear[4] != 45 || (stoi(a, 0, 10) < 1000 || stoi(a, 0, 10) > 9999) || (stoi(b, 0, 10) < 1000 || stoi(b, 0, 10) > 9999))
        return 0;
    if (IsPathExist("database//HCMUS//" + semester.schoolyear) == false) return -1;
    fstream file2;
    file2.open("database//year-semester.csv", ios::in);
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
        textBgColor(19, 15);
        DrawTextFile("_assets\\create_registration_course.txt", 15, 3);
        drawRectangle(33, 20, 50, 7, 19);
        textBgColor(0, 19);
        printtext("START DATE (DD/MM/YYYY):", 38, 21);
        printtext("END DATE (DD/MM/YYYY):", 38, 24);
        drawRectangle(38, 22, 40, 1, 15);
        drawRectangle(38, 25, 40, 1, 15);

        string filename = "database//HCMUS//" + year + "//" + semester + "//RegistrationCourseSession.txt";
        do {
            gotoxy(38, 22);
            if (insertDate(DateStart) == 0) return;
            int check = checkDate(DateStart);
            if (check == 0) {
                textBgColor(4, 15);
                gotoxy(23, 28);
                hidePointer();
                cout << "ERROR: DATE MUST HAVE FORMAT DD/MM/YYYY (01/02/2020,..), PRESS ENTER TO TRY AGAIN";
                ch = _getch();
                drawRectangle(23, 28, 90, 1, 15);
                drawRectangle(38, 22, 40, 1, 15);
                textBgColor(0, 15);
                DateStart.clear();
                showPointer();
            }
            else break;
        } while (true);
        do {
            gotoxy(38, 25);
            if (insertDate(DateEnd) == 0) return;
            int check = checkDate(DateEnd);
            if (check == 0) {
                textBgColor(4, 15);
                gotoxy(23, 28);
                hidePointer();
                cout << "ERROR: DATE MUST HAVE FORMAT LIKE DD/MM/YYYY (01/02/2020,..), PRESS ENTER TO TRY AGAIN";
                ch = _getch();
                drawRectangle(23, 28, 90, 1, 15);
                drawRectangle(38, 25, 40, 1, 15);
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
        textBgColor(19, 15);
        DrawTextFile("_assets\\create_course.txt", 15, 0);
        drawRectangle(25, 9, 70, 18, 19);
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
            if (countLine("database/HCMUS/" + year + "/" + semester + "/course_info.csv") == 1) break;
            fstream file;
            string line;
            file.open("database/HCMUS/" + year + "/" + semester + "/course_info.csv", ios::in);
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
        file.open("database/HCMUS/" + year + "/" + semester + "/course_info.csv", ios::app);
        file << endl << course.ID_course << "," << course.name << "," << course.teacher << "," << course.Num_of_creadit << "," << course.Max_student << "," << course.DayOfWeek << "," << course.session[0] << "," << course.session[1];
        file.close();
        file.open("database/HCMUS/" + year + "/" + semester + "/Course/" + course.ID_course + ".csv", ios::out);
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
    textBgColor(4, 19);
    getLineInfoForStudent(filename, 1, column, columnNum);
    for (int i = 0; i < columnNum; i++) {
        printtext(column[i], indexA[i], y);
    }
    textBgColor(0, 19);
    y++;
    int j = flagLine, h = 1;
    while (j <= line && h <= 12) {
        getLineInfoForStudent(filename, j, column, columnNum);
        for (int i = 0; i < columnNum; i++) {
            printtext(column[i], indexB[i], y);
        }
        y++; j++; h++;
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
        drawRectangle(97, 0, 22, 5, 19);
        textBgColor(4, 19);
        printtext("-[ESC]: BACK TO MENU", 97, 2);
        printtext("OR RETURN", 97, 3);
        drawRectangle(0, 0, 26, 5, 19);
        textBgColor(4, 19);
        printtext("-[x]: DELETE COURSE", 0, 0.5);
        printtext("-[ENTER]: EDIT COURSE", 0, 1.5);
        printtext("-USE UP,DOWN,LEFT,RIGHT", 0, 2.5);
        printtext("KEY TO MOVE IN EDIT STATUS", 0, 3.5);
        printtext("-[c]: CHANGE TIME", 0, 4.5);

        string filename = "database/HCMUS/" + year + "/" + semester + "/course_info.csv";
        int lineNum = countLine(filename);
        if (lineNum == 1) {
            textBgColor(4, 15);
            printtext("THERE ISN'T ANY COURSE EXIST, PRESS ENTER TO BACK TO MENU.", 30, 14);
            ch = _getch();
            textBgColor(0, 15);
            break;
        }
        drawRectangle(0, 10, 120, 15, 19);
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
    do {
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

int checkCourseSession()
{
    string year, semester;
    determineYearSemesterNow(year, semester);
    if (stoi(semester.substr(8, 1), 0, 10) == 0) {
        textBgColor(4, 15);
        printtext("HAVEN'T CREATE SEMESTER YET, PRESS ENTER TO BACK TO MENU.", 40, 10);
        char ch = _getch();
    }
    else {
        fstream file;
        file.open("database/HCMUS/" + year + "/" + semester + "/RegistrationCourseSession.txt", ios::in);
        string data;
        getline(file, data);
        if (stoi(data, 0, 10) == 0) return 0;
        else {
            getline(file, data);
            string dateStart = data.substr(12, 10);
            getline(file, data);
            string dateEnd = data.substr(9, 10);
            if (checkTimeStart(dateStart.substr(0, 2), dateStart.substr(3, 2), dateStart.substr(6, 4)) == false) return -1;//It's not time to start yet
            else {
                if (checkTimeEnd(dateEnd.substr(0, 2), dateEnd.substr(3, 2), dateEnd.substr(6, 4)) == false) return -2;//It was late to register the course
                else return 1;
            }
        }
    }
    textBgColor(0, 15);

}

bool checkTimeEnd(string date, string month, string year)
{
    int Month = stoi(month, 0, 10);
    int Year = stoi(year, 0, 10);
    int Date = stoi(date, 0, 10);
    time_t now = time(0);
    tm* ltm = localtime(&now);
    if (ltm->tm_year + 1900 < Year)
        return true;
    else {
        if (ltm->tm_year + 1900 > Year)
            return false;
        else {
            if (ltm->tm_mon + 1 < Month)
                return true;
            else {
                if (ltm->tm_mon + 1 > Month)
                    return false;
                else {
                    if (ltm->tm_mday <= Date)
                        return true;
                    else
                        return false;
                }
            }
        }
    }
}
bool checkTimeStart(string date, string month, string year)
{
    int Month = stoi(month, 0, 10);
    int Year = stoi(year, 0, 10);
    int Date = stoi(date, 0, 10);
    time_t cur = time(0);
    tm* ltm = localtime(&cur);
    if (ltm->tm_year + 1900 > Year)
        return true;
    else {
        if (ltm->tm_year + 1900 < Year)
            return false;
        else {
            if (ltm->tm_mon + 1 > Month)
                return true;
            else {
                if (ltm->tm_mon + 1 < Month)
                    return false;
                else {
                    if (ltm->tm_mday >= Date)
                        return true;
                    else
                        return false;
                }
            }
        }
    }
}
void listClass(User A, SchoolYear Y, fun_show_class Fun) {
    bool checkOut = false;
    do {
        string year = Y.year, semester = Y.semester.Name;
        char ch;
        hidePointer();
        system("cls");
        drawRectangle(97, 0, 22, 6, 19);
        textBgColor(15, 19);
        printtext("-[c]: CHANGE SCHOOL", 97, 0);
        printtext(" YEAR", 97, 1);
        printtext("-[ESC]: BACK ", 97, 3);
        printtext("-[ENTER]: CHOOSE", 97, 5);
        string filename = "database/HCMUS/" + year + "/class_info.csv";
        int lineNum = countLine(filename);
        int y = 11;
        drawRectangle(8, 10, 95, 15, 19);
        int a[5] = { 11,17,33,65,90 };
        int b[5] = { 11.5,18.5,33,72,90 };
        drawList(5, filename, y, a, b, lineNum, 2);
        hidePointer();
        int currentLine = 2, lineInConsole = 1;
        string column[5];
        getLineInfoForStudent(filename, currentLine, column, 5);
        drawRectangle(8, y + lineInConsole, 95, 1, 14);
        textBgColor(0, 14);
        for (int i = 0; i < 5; i++)
            printtext(column[i], b[i], y + lineInConsole);
        do {
            hidePointer();
            ch = _getch();
            if (ch == 27) {
                textBgColor(0, 15);
                checkOut = true;
                break;
            }
            if (ch == 72 && currentLine > 2)
            {
                currentLine--;
                lineInConsole--;
                if (lineInConsole + y <= 11) {
                    lineInConsole = 12;
                    drawRectangle(8, 10, 95, 15, 15);
                    drawRectangle(8, 10, 95, 15, 19);
                    drawList(5, filename, y, a, b, lineNum, currentLine - 11);
                    getLineInfoForStudent(filename, currentLine, column, 5);
                    drawRectangle(8, y + lineInConsole, 95, 1, 14);
                    textBgColor(0, 14);
                    for (int i = 0; i < 5; i++) {
                        printtext(column[i], b[i], y + lineInConsole);
                    }
                }
                else
                    moveUp(filename, currentLine, 5, b, y, column, lineInConsole, 95, 8);
            }
            if (ch == 80 && currentLine < lineNum)
            {
                currentLine++;
                lineInConsole++;
                if (lineInConsole + y > 23) {
                    lineInConsole = 1;
                    drawRectangle(8, 10, 95, 15, 15);
                    drawRectangle(8, 10, 95, 15, 19);
                    drawList(5, filename, y, a, b, lineNum, currentLine);
                    getLineInfoForStudent(filename, currentLine, column, 5);
                    drawRectangle(8, y + lineInConsole, 95, 1, 14);
                    textBgColor(0, 14);
                    for (int i = 0; i < 5; i++) {
                        printtext(column[i], b[i], y + lineInConsole);
                    }
                }
                else
                    moveDown(filename, currentLine, 5, b, y, column, lineInConsole, 95, 8);
            }
            if (ch == 13) {
                textBgColor(0, 15);
                Fun(A, Y, column[1]);
                break;
            }
            if (ch == 'c') {
                textBgColor(0, 15);
                change_Sem(Y);
                break;
            }
        } while (true);
        textBgColor(0, 15);
    } while (checkOut == false);
}
void showStudentInclass(User user, SchoolYear Y, string classname) {
    bool checkOut = false;
    do {
        string year = Y.year, semester = Y.semester.Name;
        char ch;
        hidePointer();
        system("cls");
        drawRectangle(97, 0, 22, 6, 19);
        textBgColor(4, 19);
        printtext("-[c]: CHANGE SCHOOL", 97, 0);
        printtext(" YEAR", 97, 1);
        printtext("-[ESC]: BACK TO MENU", 97, 3);
        string filename = "database/HCMUS/" + year + "/" + classname + ".csv";
        int lineNum = countLine(filename);
        int y = 11;
        drawRectangle(8, 10, 100, 15, 19);
        int a[6] = { 8,18,36,64,85,95 };
        int b[6] = { 8,18,36,64,85,95 };
        drawList(6, filename, y, a, b, lineNum, 2);
        hidePointer();
        int currentLine = 2, lineInConsole = 1;
        string column[6];
        getLineInfoForStudent(filename, currentLine, column, 6);
        drawRectangle(8, y + lineInConsole, 100, 1, 14);
        textBgColor(0, 14);
        for (int i = 0; i < 6; i++)
            printtext(column[i], b[i], y + lineInConsole);
        do {
            hidePointer();
            ch = _getch();
            if (ch == 27) {
                textBgColor(0, 15);
                checkOut = true;
                break;
            }
            if (ch == 72 && currentLine > 2)
            {
                currentLine--;
                lineInConsole--;
                if (lineInConsole + y <= 11) {
                    lineInConsole = 12;
                    drawRectangle(8, 10, 100, 15, 15);
                    drawRectangle(8, 10, 100, 15, 19);
                    drawList(6, filename, y, a, b, lineNum, currentLine - 11);
                    getLineInfoForStudent(filename, currentLine, column, 6);
                    drawRectangle(8, y + lineInConsole, 100, 1, 14);
                    textBgColor(0, 14);
                    for (int i = 0; i < 6; i++) {
                        printtext(column[i], b[i], y + lineInConsole);
                    }
                }
                else
                    moveUp(filename, currentLine, 6, b, y, column, lineInConsole, 100, 8);
            }
            if (ch == 80 && currentLine < lineNum) //down
            {
                lineInConsole++;
                currentLine++;
                if (lineInConsole + y > 23) {
                    lineInConsole = 1;
                    drawRectangle(8, 10, 100, 15, 15);
                    drawRectangle(8, 10, 100, 15, 19);
                    drawList(6, filename, y, a, b, lineNum, currentLine);
                    getLineInfoForStudent(filename, currentLine, column, 6);
                    drawRectangle(8, y + lineInConsole, 100, 1, 14);
                    textBgColor(0, 14);
                    for (int i = 0; i < 6; i++) {
                        printtext(column[i], b[i], y + lineInConsole);
                    }
                }
                else
                    moveDown(filename, currentLine, 6, b, y, column, lineInConsole, 100, 8);
            }
        } while (true);
        textBgColor(0, 15);
    } while (checkOut == false);
}