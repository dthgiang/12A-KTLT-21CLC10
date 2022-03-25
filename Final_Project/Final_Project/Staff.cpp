#include "Staff.h"

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
