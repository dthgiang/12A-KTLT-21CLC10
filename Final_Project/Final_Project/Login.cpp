#include "Login.h"

void LoginGUI()
{
	drawRectangle(3, 1, 115, 8, 19);
    drawRectangle(3, 23.5, 115, 5, 19);
	//drawRectangle(3, 23.5, 115, 5.5, 19);
    drawRectangle(3, 9, 115, 14, 15);
	textBgColor(15, 19);
	DrawText("_assets\\login_bg1.txt", 29, 0);
    DrawText("_assets\\login_bg2.txt", 9, 23);

    drawRectangle(47, 11, 27, 9, 19);
    DrawText("_assets\\login_username.txt", 48, 12);
    DrawText("_assets\\login_password.txt", 48, 15);

    drawRectangle(48, 13, 25, 1, 15);
    drawRectangle(48, 16, 25, 1, 15);
    gotoxy(48, 18);
    cout << "ENTER TO LOGIN" << endl << endl;
}
