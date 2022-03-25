#include "ConsoleGUI.h"
#include "Login.h"
#include "Graphics.h"
#include "Menu.h"
int main()
{
	FixConsoleWindow();
	//cout << "Group 12A" << endl;
	//DrawText("_assets//login_bg.txt", 25, 5);
	User dthgiang;
	LoginLoop(dthgiang);
	//DrawStaffMenu();
	
	return 0;
}