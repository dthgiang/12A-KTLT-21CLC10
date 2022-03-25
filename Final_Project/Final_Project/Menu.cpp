#include "Menu.h"

void drawASCIIStaffMenu() {
    SchoolYear SY;

    drawRectangle(3, 1, 115, 8, 19);
    drawRectangle(3, 23.5, 115, 5, 19);
    drawRectangle(3, 22, 115, 1, 19);

    drawRectangle(3, 9, 115, 14, 15);
    drawRectangle(3, 26, 115, 1, 19);
    textBgColor(15, 19);
    
    DrawTextFile("_assets\\menu_staff1.txt", 20, 1);
    DrawTextFile("_assets\\login_bg2.txt", 9, 23);

    cout << "     " << SY.semester.Name << " - " << SY.year << "     ";
    gotoxy(43, 22);
    textBgColor(0, 15);
}