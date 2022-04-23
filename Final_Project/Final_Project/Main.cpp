#include "ConsoleGUI.h"
#include "Login.h"
#include "Graphics.h"
int main()
{
	FixConsoleWindow();
	User user;
	LoginLoop(user);
	return 0;
}