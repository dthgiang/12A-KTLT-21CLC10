#include "Change_Password.h"

void Rewrite_Info(User user) {
    fstream file_prv, file_aft;
    string oldName = "database/login.csv";
    string newName = "database/login_after_change_password.csv";
    file_prv.open(oldName, ios::in);
    file_aft.open(newName, ios::out);
    string temp;
    while (file_prv.eof() == false) {
        getline(file_prv, temp, ',');
        file_aft << temp << ',';
        if (user.ID.compare(temp) != 0) {
            getline(file_prv, temp);
            file_aft << temp << '\n';
        }
        else {
            getline(file_prv, temp);
            string temp1 = user.Password + ',' + to_string(user.role);
            if (user.role == 1) {
                temp1 = temp1 + ',' + user.info.Class;
            }
            file_aft << temp1 << '\n';
        }
    }
    file_prv.close();
    file_aft.close();
    // removing the existing file
    remove(oldName.c_str());
    // renaming the updated file with the existing file name
    rename(newName.c_str(), oldName.c_str());
};

void Change_Password(User& user) {

    system("cls");

    drawRectangle(3, 3, 115, 8, 19);
    textBgColor(15, 19);
   
    DrawTextFile("_assets\\change_password.txt", 8, 4);
    drawRectangle(45, 15, 27, 12, 19);
    printtext("YOUR PASSWORD :", 46, 16);
    printtext("ENTER NEW PASSWORD :", 46, 19);
    printtext("ENTER NEW PASSWORD AGAIN :", 46, 22);

    drawRectangle(46, 17, 25, 1, 15);
    drawRectangle(46, 20, 25, 1, 15);
    drawRectangle(46, 23, 25, 1, 15);
    gotoxy(46, 17);
    string temp;
    InsertPassword(temp);

    if (temp.compare(user.Password) == 0) {
        gotoxy(46, 20);
        string temp1;
        InsertPassword(temp);
        gotoxy(46, 23);
        InsertPassword(temp1);
        if (temp.compare(temp1) == 0) {
            user.Password = temp;
            gotoxy(46, 25);
            cout << "Successfully! \n";
            Rewrite_Info(user);
        }
        else {
            gotoxy(46, 25);
            cout << "Password does not match.\n";
        }
    }
    else {
        gotoxy(46, 18);
        cout << "Incorrect password. \n";
    }
    system("pause");
    
}