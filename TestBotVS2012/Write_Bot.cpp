#include <conio.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "EnumKey.h"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
using namespace std;

int main()
{
	ofstream bot ("bot_track.txt",ofstream::binary);

    int c = 0;
	bool quit = false;
	bool *isdown = new bool[256];
	bool *ispressed = new bool[256];
	Clock::time_point *timers = new Clock::time_point[256];

	// init arrays of booleans
	for (int i = 0; i < (sizeof(isdown) /sizeof(isdown[0])); i++) {
		isdown[i] = false;
	}
	for (int i = 0; i < (sizeof(ispressed) /sizeof(ispressed[0])); i++) {
		ispressed[i] = false;
	}
	// wait to start
    while(!quit)
    {
		if (GetKeyState(VK_PRIOR) & 0x8000) {
			quit = true;
		}
	}
	quit = false;
	// timer started
	Clock::time_point timer_start = Clock::now();
	// LOOP WHILE PAGE DOWN
    while(!quit)
    {
		// LOOP FOR EACH KEY
		for (int x=0; x < (sizeof(keycodes) / sizeof(keycodes[0])); x++) {
			// KEY IS BEING PRESSED
			if (GetKeyState(keycodes[x]) & 0x8000) {
				if (keycodes[x] == VK_NEXT) {
					quit = true;
				}
				else {
					if (isdown[x] == false){
						isdown[x] = true;
						timers[x] = Clock::now();
					//	cout << "BEGIN " << std::chrono::duration_cast<std::chrono::nanoseconds>(timers[x] - t1).count() << " " << keycodes[x] << endl;
					}					
				}
			}
			// KEY RELEASED OR NO KEYS
			else {
				if (isdown[x] == true) {
						Clock::duration begintime = timers[x] - timer_start;
						Clock::duration finaltime = Clock::now() - timers[x];
						bot << "BEGIN " << begintime.count() << " END " << finaltime.count() << " " << keycodes[x] << endl;
						cout << "BEGIN " << begintime.count() << " END " << finaltime.count() << " " << keycodes[x] << endl;
				}
				isdown[x] = false;
			}
		}
    }

    return 0;
	bot.close();
}


//------------------------------------------------- MOUSE -------------------------------------------------
/*#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <windows.h>


#define X 123
#define Y 123
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800


void MouseSetup(INPUT *buffer)
{
    buffer->type = INPUT_MOUSE;
    buffer->mi.dx = (0 * (0xFFFF / SCREEN_WIDTH));
    buffer->mi.dy = (0 * (0xFFFF / SCREEN_HEIGHT));
    buffer->mi.mouseData = 0;
    buffer->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
    buffer->mi.time = 0;
    buffer->mi.dwExtraInfo = 0;
}


void MouseMoveAbsolute(INPUT *buffer, int x, int y)
{
    buffer->mi.dx = (x * (0xFFFF / SCREEN_WIDTH));
    buffer->mi.dy = (y * (0xFFFF / SCREEN_HEIGHT));
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);

    SendInput(1, buffer, sizeof(INPUT));
}


void MouseClick(INPUT *buffer)
{
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
    SendInput(1, buffer, sizeof(INPUT));

    Sleep(10);

    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
    SendInput(1, buffer, sizeof(INPUT));
}


int main(int argc, char *argv[])
{
    INPUT buffer[1];

    MouseSetup(&buffer);

    MouseMoveAbsolute(&buffer, X, Y);
    MouseClick(&buffer);

    return 0;
}*/










































// /!\ 224 = getch additional key, H K P N = left/right/down/Up, 224 80 = DOWN

// old code, just in case.
/*
		if( GetKeyState(VK_LCONTROL) & 0x8000)
		{
			if (isdown[0] == false) {
				isdown[0] = true;
				bot << "LCTRL" << endl;
			}
			auto t2 = Clock::now();
			cout << "T " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " LCTRL" << endl;

		}
		else 
			isdown[0] = false;



		if( GetAsyncKeyState(VK_LSHIFT) != 0)
		{
			if (isdown[0] == false) {
				isdown[0] = true;
				bot << "LSHIFT" << endl;
				cout << "LSHIFT" << endl;
			}
		}
		if( GetAsyncKeyState(VK_LMENU) != 0)
		{
			if (isdown[0] == false) {
				isdown[0] = true;
				bot << "LALT" << endl;
				cout << "LALT" << endl;
			}
		}
		if( GetAsyncKeyState(VK_RCONTROL) != 0)
		{
			if (isdown[0] == false) {
				isdown[0] = true;
				bot << "RCTRL" << endl;
				cout << "RCTRL" << endl;
			}
		}
		if( GetAsyncKeyState(VK_RSHIFT) != 0)
		{
			if (isdown[0] == false) {
				isdown[0] = true;
				bot << "RSHIFT" << endl;
				cout << "RSHIFT" << endl;
			}
		}
		if( GetAsyncKeyState(VK_RMENU) != 0)
		{
			if (isdown[0] == false) {
				isdown[0] = true;
				bot << "RALT" << endl;
				cout << "RALT" << endl;
			}
		}
		if( GetAsyncKeyState(VK_ESCAPE) != 0)
		{
			if (isdown[0] == false) {
				isdown[0] = true;
				bot << "ESC" << endl;
				cout << "ESC" << endl;
				quit = true;
			}
		}
		if( GetAsyncKeyState(0x30) != 0)
		{
			if (isdown[0] == false) {
				isdown[0] = true;
				bot << "0" << endl;
				cout << "0" << endl;
			}
		}
		if( GetAsyncKeyState(VK_LEFT) != 0)
		{
			if (isdown[0] == false) {
				isdown[0] = true;
				bot << "LEFT" << endl;
				cout << "LEFT" << endl;
			}
		}
		if( GetAsyncKeyState(VK_RIGHT) != 0)
		{
			if (isdown[0] == false) {
				isdown[0] = true;
				bot << "RIGHT" << endl;
				cout << "RIGHT" << endl;
			}
		}
		if( GetAsyncKeyState(VK_DOWN) != 0)
		{
			//if (isdown == false) {
			//	isdown = true;
				bot << "DOWN" << endl;
				cout << "DOWN" << endl;
			//}
		}
	//	else
		//	isdown = false;
		if( GetAsyncKeyState(VK_UP) != 0)
		{
			//if (isdown == false) {
			//	isdown = true;
				bot << "UP" << endl;
				cout << "UP" << endl;
			//}
		}
	//	else
		//	isdown = false;*/