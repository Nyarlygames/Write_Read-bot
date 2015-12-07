#include <conio.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int main()
{
	ofstream bot ("bot_track.txt",ofstream::binary);

    int c = 0;
	bool quit = false;
	bool isdown = false;
	// need to have :
	// 1 bool for key press detected
	// 1 bool for key is still being pressed
	// = 2 bools per keys (simultaneous inputs)


	// timer starts
	// auto t1 = Clock::now();
	// get timer (can be reused)
	// auto t2 = Clock::now();
	// value since t1 :
	// std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()


	auto t1 = Clock::now();

    while(!quit)
    {
		// SPECIAL KEYS
		if( GetAsyncKeyState(VK_LCONTROL) != 0)
		{
			if (isdown == false) {
				isdown = true;
				bot << "LCTRL" << endl;
				auto t2 = Clock::now();
				cout << "T " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " LCTRL" << endl;
			}
		}
		else 
			isdown = false;
		if( GetAsyncKeyState(VK_LSHIFT) != 0)
		{
			if (isdown == false) {
				isdown = true;
				bot << "LSHIFT" << endl;
				cout << "LSHIFT" << endl;
			}
		}
		if( GetAsyncKeyState(VK_LMENU) != 0)
		{
			if (isdown == false) {
				isdown = true;
				bot << "LALT" << endl;
				cout << "LALT" << endl;
			}
		}
		if( GetAsyncKeyState(VK_RCONTROL) != 0)
		{
			if (isdown == false) {
				isdown = true;
				bot << "RCTRL" << endl;
				cout << "RCTRL" << endl;
			}
		}
		if( GetAsyncKeyState(VK_RSHIFT) != 0)
		{
			if (isdown == false) {
				isdown = true;
				bot << "RSHIFT" << endl;
				cout << "RSHIFT" << endl;
			}
		}
		if( GetAsyncKeyState(VK_RMENU) != 0)
		{
			if (isdown == false) {
				isdown = true;
				bot << "RALT" << endl;
				cout << "RALT" << endl;
			}
		}
		if( GetAsyncKeyState(VK_ESCAPE) != 0)
		{
			if (isdown == false) {
				isdown = true;
				bot << "ESC" << endl;
				cout << "ESC" << endl;
				quit = true;
			}
		}
		if( GetAsyncKeyState(0x30) != 0)
		{
			if (isdown == false) {
				isdown = true;
				bot << "0" << endl;
				cout << "0" << endl;
			}
		}
		if( GetAsyncKeyState(VK_LEFT) != 0)
		{
			if (isdown == false) {
				isdown = true;
				bot << "LEFT" << endl;
				cout << "LEFT" << endl;
			}
		}
		if( GetAsyncKeyState(VK_RIGHT) != 0)
		{
			if (isdown == false) {
				isdown = true;
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
		//	isdown = false;
    }

    return 0;
	bot.close();
}


// /!\ 224 = getch additional key, H K P N = left/right/down/Up, 224 80 = DOWN