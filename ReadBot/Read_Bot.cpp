#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <cstring>

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ";

int main()
{
  // create a file-reading object
  ifstream fin;
  struct



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
	if (n> 0){
		//cout << token[0] << token[1] << token[2] << token[3] << token[4] << endl;
		//  1 : begin time
		//  3 : end time
		//  4 : Key
	}

	/*
        ip.ki.wVk = VK_SPACE;
        ip.ki.dwFlags = 0; // 0 for key press
        //SendInput(1, &ip, sizeof(INPUT));
        SendInput(1, &ip, sizeof(INPUT));
		Sleep(2000);
        ip.ki.wVk = VK_SPACE;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
		*/



  }
  /* debug read */
	_sleep(5000);
  fin.close();
}