#include "Login.h"
#include "ConsoleGUI.h"
#include "Menu.h"
#include "Graphics.h"

void LoginGUI(User &User)
{
    showPointer();
    textBgColor(2, 0);
    system("cls");

    User.ID = User.Password = "";
	drawRectangle(3, 1, 115, 8, 19);
    drawRectangle(3, 23.5, 115, 5, 19);
	
    drawRectangle(3, 9, 115, 14, 15);
	textBgColor(15, 19);

	DrawTextFile("_assets\\login_bg1.txt", 29, 0);
    DrawTextFile("_assets\\login_bg2.txt", 9, 23);

    drawRectangle(47, 11, 27, 10, 19);
    DrawTextFile("_assets\\login_Username.txt", 48, 12);
    DrawTextFile("_assets\\login_password.txt", 48, 15);

    drawRectangle(48, 13, 25, 1, 15);
    drawRectangle(48, 16, 25, 1, 15);
    gotoxy(48, 18);
    cout << "ENTER TO LOGIN" << endl << endl;

    gotoxy(48, 13);
    InsertUserName(User.ID);

    gotoxy(48, 16);
    InsertPassword(User.Password);
}


void InsertUserName(string& Username)
{
    showPointer();
    char key = _getch();
    while (key != TAB)
    {
        if (key == SPACE)
        {
            if (Username.size() > 0)
            {
                Username.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        //Other key
        else if (key >= 33 && key <= 126 && Username.size() <= 15)
        {
            cout << key;
            Username.push_back(key);
        }
        key = _getch();
    }
}

void InsertPassword(string& Password)
{
    showPointer();
    Password = "";
    char key = _getch();
    while (key != ENTER)
    {
        if (key == SPACE)
        {
            if (Password.size() > 0)
            {
                Password.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        //Other key
        else if (key >= 33 && key <= 126 && Password.size() <= 15)
        {
            cout << "*";
            Password.push_back(key);
        }
        key = _getch();
    }
}

int CheckStatusLogin(User& User) {
    fstream filename1, filename2;
    filename1.open("database/login.csv", ios::in);
    filename2.open("database/login.csv", ios::in);

    if (!filename1.is_open() || !filename2.is_open())
        cout << "Can't open file!";

    string nRow, nCol;
    int Users;
    bool isCheck = 0;
    while (!filename1.eof())
    {
        getline(filename1, nRow);
        while (!filename2.eof())
        {
            getline(filename2, nCol, '-');
            if (nCol.compare(User.ID) == 0) {
                getline(filename2, nCol, '-');
                if (nCol.compare(User.Password) == 0) {
                    isCheck = 1;
                    getline(filename2, nCol, '-');
                    Users = stoi(nCol, 0, 10);
                    break;
                }
            }
            getline(filename2, nCol);
            break;
        }
        if (isCheck == 1) break;
    }

    if (isCheck == 0) return -1;

    User.role = Users;
    if (Users == 1) {
        getline(filename2, nCol, '\n');
        User.info.Class = nCol;
    }

    filename1.close();
    filename2.close();

    return Users;
}

void LoginLoop(User& User)
{
    textColor(0);
    do
    {
        system("cls");
        LoginGUI(User);

        if (CheckStatusLogin(User) == -1)
        {
            gotoxy(48, 20);
            cout << "LOGIN FAIL";
            hidePointer();
            Sleep(900);
        }
    } while (CheckStatusLogin(User) == -1);
    gotoxy(48, 20);
    cout << "LOGIN SUCCESSFUL!";
    hidePointer();
    Sleep(900);
    system("cls");
    if (User.role == 1) return;// menuStudent(user);
    else StaffMenu(User);
}
