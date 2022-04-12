#include "ConsoleGUI.h"
#include "Login.h"
#include "Graphics.h"
int main()
{
	FixConsoleWindow();
	User dthgiang;
	LoginLoop(dthgiang);
	return 0;
}