#include <iostream>
#include <Windows.h>
#include <Windowsx.h>

#include "ScreenCapture.h"

using namespace std;

DWORD reset = VK_BACK;
DWORD setup = VK_RETURN;
DWORD setPos = VK_LBUTTON;
DWORD display = VK_SPACE;

bool keyListener(int key)
{
	bool pressed = false;

	while (GetAsyncKeyState(key) < 0)
		pressed = true;

	return pressed;
}

void welcomeMessage()
{
	cout << "Hello, welcome to my color selector. Press 'enter' to begin setting values.\n" << endl;
	cout << "Set color values by clicking anywhere on your screen.\n" << endl;
	cout << "Press 'enter' again to stop selecting colors.\n" << endl;
	cout << "You can press 'space' to view your color values and positions and 'backspace' to reset them.\n" << endl;
	cout << "Enjoy!" << endl;
}

int main()
{
	POINT pt;
	ScreenCapture capture;

	bool set_value = false;
	bool canClick = false;

	int xPos = 0;
	int yPos = 0;

	int placeValue = -1;

	unsigned int c[3] = {0, 0, 0};

	int colors[5][3];
	int positions[5][2];

	welcomeMessage();

	while (true)
	{
		// update the screen
		capture.CaptureScreen();

		// listen for setup key
		if (keyListener(setup))
		{
			canClick = !canClick;

			if (canClick)
			{
				printf("\nYou can now set values!\n");
			}else
			{
				printf("\nYou can no longer set values!\n");
			}
		}

		// listen for setPos key
		if (keyListener(setPos) && canClick) 
		{
			GetCursorPos(&pt);

			if (placeValue < 4)
			{
				++placeValue;
				printf("Value %d/5 set!\n", placeValue+1);
			}
			else
			{
				printf("\nYou have reached the maximum!\n");
			}

			xPos = pt.x;
			yPos = pt.y;

			c[0] = capture.PosR(xPos, yPos);
			c[1] = capture.PosG(xPos, yPos);
			c[2] = capture.PosB(xPos, yPos);

			set_value = true;
		}

		// listen for the display key
		if (keyListener(display))
		{
			if (placeValue > -1)
			{
				for (int i = 0; i <= placeValue; i++)
				{
					printf("\nValue %d\n", i+1);
					printf("X: %d, Y: %d\n", positions[i][0], positions[i][1]);
					printf("R: %d, G: %d, B: %d\n", colors[i][0], colors[i][1], colors[i][2]);
				}
			}
			else
			{
				printf("\nYou haven't set any values!\n");
			}
		}

		// listen for reset key
		if (keyListener(reset))
		{
			for (int i = 0; i <= placeValue; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					colors[i][j] = 0;
				}

				for (int k = 0; k < 2; k++)
				{
					positions[i][k] = 0;
				}
			}
			placeValue = -1;
			printf("\nValues reset!\n");
		}

		// set original rgb's
		if (set_value)
		{
			for (int i = 0; i < 3; i++)
			{
				colors[placeValue][i] = c[i];
			}

			positions[placeValue][0] = xPos;
			positions[placeValue][1] = yPos;

			set_value = false;
		}
	}

	return 0;
}