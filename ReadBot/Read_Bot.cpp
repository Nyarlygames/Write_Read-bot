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
typedef std::chrono::high_resolution_clock Clock;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const int MAXCMD = 1000;
const char* const DELIMITER = " ";

struct Command {
	int start;
	int end;
	int keycode;
};

INPUT ip;

int main()
{
  // create a file-reading object
	ifstream fin;
	ofstream log ("log.txt",ofstream::binary);
	Command	*listcmd = new Command[MAXCMD];
	int nbcmd = 0;

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
		cout << n << endl;

		// Populate list of cmd
		if (n> 0){
			//  1 : begin time
			//  3 : end time
			//  4 : Key
			listcmd[nbcmd].start = atoi(token[1]);
			listcmd[nbcmd].end = atoi(token[3]) + atoi(token[1]);
			listcmd[nbcmd].keycode = atoi(token[4]);
			cout << "NBCMD : " << nbcmd << " Start : " << listcmd[nbcmd].start << " End : " << listcmd[nbcmd].end << " Key : " << listcmd[nbcmd].keycode << endl;
		}
		nbcmd++;
	}
	
	ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
	int curcmd = 0;
	Clock::time_point timer_start = Clock::now();
	Clock::duration new_time;

	// if loop mode
	if (loop == true) {
		while (!quit) {
			while (curcmd < nbcmd-1) {
				if (GetKeyState(VK_NEXT) & 0x8000) {
					quit = true;
				}
				for (int i = curcmd; i < nbcmd-1; i++) {
					new_time = Clock::now() - timer_start;
					// If key is being pressed at that time
					if ((new_time.count() >= listcmd[i].start ) && (new_time.count() <= listcmd[i].end)) {
						ip.ki.wVk = listcmd[i].keycode;
						ip.ki.dwFlags = 0; // 0 for key press
						SendInput(1, &ip, sizeof(INPUT));
						cout << "key sent : " << listcmd[i].keycode << endl;
						log << "key sent : " << listcmd[i].keycode << endl;
					}
					// If key is released
					else if (new_time.count() > listcmd[i].end) {
						ip.ki.wVk = listcmd[i].keycode;
						ip.ki.dwFlags = KEYEVENTF_KEYUP;
						SendInput(1, &ip, sizeof(INPUT));
						curcmd++;
						cout << "key ended : " << listcmd[i].keycode << endl;
						log << "key ended : " << listcmd[i].keycode << endl;
					}
				}
			}
			new_time = Clock::now() - timer_start;
			// Restart bot TODO because not working...
			if ((curcmd == nbcmd) && (new_time.count() > listcmd[curcmd-1].end)) {
				curcmd = 0;
				timer_start = Clock::now();
			}
		}
	}
	// else single read
	else {
		while (curcmd < nbcmd-1) {
			for (int i = curcmd; i < nbcmd-1; i++) {
				Clock::duration new_time = Clock::now() - timer_start;
				// If key is being pressed at that time
				if ((new_time.count() >= listcmd[i].start ) && (new_time.count() <= listcmd[i].end)) {
					ip.ki.wVk = listcmd[i].keycode;
					ip.ki.dwFlags = 0; // 0 for key press
					SendInput(1, &ip, sizeof(INPUT));
					cout << "key sent : " << listcmd[i].keycode << endl;
					log << "key sent : " << listcmd[i].keycode << endl;
				}
				// If key is released
				else if (new_time.count() > listcmd[i].end) {
					ip.ki.wVk = listcmd[i].keycode;
					ip.ki.dwFlags = KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					curcmd++;
					cout << "key ended : " << listcmd[i].keycode << endl;
					log << "key ended : " << listcmd[i].keycode << endl;
				}
				//cout << "Starttime  " << listcmd[i].start << " Newtime :" << new_time.count() << " Endtime : " << listcmd[i].end << endl;
			//	cout << "TIME : " << new_time.count() << " Starttime  " << listcmd[i].start << " Endtime : " << listcmd[i].end << " Key : " << listcmd[i].keycode << " Curcmd : " << curcmd << "Nbcmd : " << nbcmd << endl;
			}
		}
	}

	/* debug read */
	//_sleep(5000);
	fin.close();
	return(0);
}