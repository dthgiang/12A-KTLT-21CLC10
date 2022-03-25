#include "System_Function.h"

void drawMenu(string* S, int n, int x, int y, int dis, drawTxt function)
{
	hidePointer();
	int maxlength = 0;
	maxlength += 1;
	function();
	drawRectangle(x - 10, y, maxlength, n + (n - 1) * dis, 19);
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			drawRectangle(x, y, maxlength - 20, 1, 0);
			textBgColor(15, 0);
			printtext(S[i], x, y + (dis + 1) * i);
		}
		else
			textBgColor(0, 15);
		printtext(S[i], x, y + (dis + 1) * i);
		textBgColor(0, 15);
	}
}
