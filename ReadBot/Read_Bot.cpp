#define _CRT_SECURE_NO_WARNINGS
#define WINVER 0x0500
#include <windows.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
typedef std::chrono::steady_clock Clock;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const int MAXCMD = 5000;
const int MAXMOVE = 5000;
const char* const DELIMITER = " ";

struct Command {
	int start;
	int end;
	int keycode;
	bool sent;
};
struct Movement {
	int x;
	int y;
	int time;
	bool moved;
};

INPUT ip;
INPUT mip;
INPUT mip_click;

int main()
{
  // create a file-reading object
	ifstream fin;
	ofstream log ("log.txt",ofstream::binary);
	Command	*listcmd = new Command[MAXCMD];
	Movement *listmove = new Movement[MAXMOVE];
	int nbcmd = 0;
	int nbmove = 0;

	bool quit = false;
	bool loop = false;

    while(!quit)
    {
		if (GetKeyState(VK_PRIOR) & 0x8000) {
			quit = true;
		}
		if (GetKeyState(VK_HOME) & 0x8000) {
			loop = true;
			quit = true;
		}
	}
	quit = false;
	fin.open("bot_track.txt"); // open a file
	if (!fin.good()) 
	return 1; // exit if file not found
  
	// read each line of the file
	while (!fin.eof())
	{
		// read an entire line into memory
		char buf[MAX_CHARS_PER_LINE];
		fin.getline(buf, MAX_CHARS_PER_LINE);
    
		// parse the line into blank-delimited tokens
		int n = 0; // a for-loop index
    
		// array to store memory addresses of the tokens in buf
		const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
    

		// parse the line
		token[0] = strtok(buf, DELIMITER); // first token
		if (token[0]) // zero if line is blank
		{
			for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
			{
			token[n] = strtok(0, DELIMITER); // subsequent tokens
			if (!token[n]) {
					break;
			}// no more tokens
			}
		}

		// Populate list of cmd
		if (n> 0){
			//  1 : begin time
			//  3 : end time
			//  4 : Key
			if (!strcmp(token[0], "BEGIN")) {
				listcmd[nbcmd].start = atoi(token[1]);
				listcmd[nbcmd].end = atoi(token[3]) + atoi(token[1]);
				listcmd[nbcmd].keycode = atoi(token[4]);
				listcmd[nbcmd].sent = false;
			//	cout << "NBCMD : " << nbcmd << " Start : " << listcmd[nbcmd].start << " End : " << listcmd[nbcmd].end << " Key : " << listcmd[nbcmd].keycode << endl; 
				nbcmd++;
			}
			else if (!strcmp(token[0], "MOUSE")) {
				listmove[nbmove].x = atoi(token[2]);
				listmove[nbmove].y = atoi(token[4]);
				listmove[nbmove].time = atoi(token[6]);
				listmove[nbmove].moved = false;
				nbmove++;
			}
		}
	}
	mip.type = INPUT_MOUSE;
	mip.mi.mouseData=0;
	mip.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	mip_click.type = INPUT_MOUSE;
	mip_click.mi.mouseData=0;
	mip_click.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
	int curcmd = 0;
	int curmove = 0;
	Clock::time_point timer_start = Clock::now();
	Clock::duration new_time;

	// if loop mode
	if (loop == true) {
		while (!quit) {
			if (GetKeyState(VK_NEXT) & 0x8000) {
				quit = true;
			}
			if (curcmd < nbcmd) {
				for (int i = curcmd; i < nbcmd; i++) {
					new_time = Clock::now() - timer_start;
					// If key is being pressed at that time
					if ((new_time.count() >= listcmd[i].start ) && (new_time.count() <= listcmd[i].end) && (listcmd[i].sent == false)) {
					
						//mousebuttons
						if (listcmd[i].keycode == VK_LBUTTON) {
							mip_click.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
							SendInput(1, &mip_click, sizeof(mip_click));
						}
						else if (listcmd[i].keycode == VK_RBUTTON) {
							mip_click.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
							SendInput(1, &mip_click, sizeof(mip_click));
						}
						else {
							ip.ki.wVk = listcmd[i].keycode;
							ip.ki.dwFlags = 0; // 0 for key press
							SendInput(1, &ip, sizeof(INPUT));
						}
						listcmd[i].sent = true;
					}
					// If key is released
					else if (new_time.count() > listcmd[i].end) {
						//mousebuttons
						if (listcmd[i].keycode == VK_LBUTTON) {
							mip_click.mi.dwFlags = MOUSEEVENTF_LEFTUP;
							SendInput(1, &mip_click, sizeof(mip_click));
						}
						else if (listcmd[i].keycode == VK_RBUTTON) {
							mip_click.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
							SendInput(1, &mip_click, sizeof(mip_click));
						}
						else {
							ip.ki.wVk = listcmd[i].keycode;
							ip.ki.dwFlags = KEYEVENTF_KEYUP;
							SendInput(1, &ip, sizeof(INPUT)); 
						}
						curcmd++;
						listcmd[i].sent = false;
					}
				}
			}
			
			/*if (curmove < nbmove) {
				for (int j = curmove; j < nbmove; j++) {
					Clock::duration move_time = Clock::now() - timer_start;
					if ((move_time.count() >= listmove[j].time ) && (listmove[j].moved == false)) {
						mip.mi.dx =  listmove[j].x*(65536/GetSystemMetrics(SM_CXSCREEN));//x being coord in pixels
						mip.mi.dy =  listmove[j].y*(65536/GetSystemMetrics(SM_CYSCREEN));//y being coord in pixels
						SendInput(1,&mip,sizeof(mip));
						listmove[j].moved = true;
						curmove++;
					}
				}
			}*/
			// Restart bot.
			new_time = Clock::now() - timer_start;
			if ((curcmd == nbcmd)/* && (curmove == nbmove)*/ && (new_time.count() > listcmd[curcmd-1].end)) {
				curcmd = 0;
			//	curmove = 0;
				timer_start = Clock::now();

			}
		}
	}
	// else single read
	else {
		while (curcmd < nbcmd) {
			for (int i = curcmd; i < nbcmd; i++) {
				 new_time = Clock::now() - timer_start;
				// If key is being pressed at that time
				if ((new_time.count() >= listcmd[i].start ) && (new_time.count() <= listcmd[i].end) && (listcmd[i].sent == false)) {
					
					//mousebuttons
					if (listcmd[i].keycode == VK_LBUTTON) {
						mip_click.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
						SendInput(1, &mip_click, sizeof(mip_click));
					}
					else if (listcmd[i].keycode == VK_RBUTTON) {
						mip_click.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
						SendInput(1, &mip_click, sizeof(mip_click));
					}
					else {
						ip.ki.wVk = listcmd[i].keycode;
						ip.ki.dwFlags = 0; // 0 for key press
						SendInput(1, &ip, sizeof(INPUT));
					}
					listcmd[i].sent = true;
				}
				// If key is released
				else if (new_time.count() > listcmd[i].end) {
					//mousebuttons
					if (listcmd[i].keycode == VK_LBUTTON) {
						mip_click.mi.dwFlags = MOUSEEVENTF_LEFTUP;
						SendInput(1, &mip_click, sizeof(mip_click));
					}
					else if (listcmd[i].keycode == VK_RBUTTON) {
						mip_click.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
						SendInput(1, &mip_click, sizeof(mip_click));
					}
					else {
						ip.ki.wVk = listcmd[i].keycode;
						ip.ki.dwFlags = KEYEVENTF_KEYUP;
						SendInput(1, &ip, sizeof(INPUT)); 
					}
					curcmd++;
					listcmd[i].sent = false;
				}
			}
			
			for (int j = curmove; j < nbmove; j++) {
				Clock::duration move_time = Clock::now() - timer_start;
				if ((move_time.count() >= listmove[j].time ) && (listmove[j].moved == false)) {
					mip.mi.dx =  listmove[j].x*(65536/GetSystemMetrics(SM_CXSCREEN));//x being coord in pixels
					mip.mi.dy =  listmove[j].y*(65536/GetSystemMetrics(SM_CYSCREEN));//y being coord in pixels
					SendInput(1,&mip,sizeof(mip));
					listmove[j].moved = true;
					curmove++;
				}
			}
		}
	}

	fin.close();
	return(0);
}
