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
    DrawTextFile("change_password.txt", 10, 4);
    drawRectangle(47, 15, 27, 12, 11);
    printtext("YOUR PASSWORD :", 48, 16);
    printtext("ENTER NEW PASSWORD :", 48, 19);
    printtext("ENTER NEW PASSWORD AGAIN :", 48, 22);

    drawRectangle(48, 17, 25, 1, 15);
    drawRectangle(48, 20, 25, 1, 15);
    drawRectangle(48, 23, 25, 1, 15);
    gotoxy(48, 17);
    string temp;
    InsertPassword(temp);
    if (temp.compare(user.Password) == 0) {
        gotoxy(48, 20);
        string temp1;
        InsertPassword(temp);
        gotoxy(48, 23);
        InsertPassword(temp1);
        if (temp.compare(temp1) == 0) {
            user.Password = temp;
            gotoxy(46, 25);
            cout << "Change password successfully \n";
            Rewrite_Info(user);
        }
        else {
            gotoxy(48, 25);
            cout << "Password does not match.\n";
        }
    }
    else {
        gotoxy(48, 18);
        cout << "Incorrect password. \n";
    }
    system("pause");
}