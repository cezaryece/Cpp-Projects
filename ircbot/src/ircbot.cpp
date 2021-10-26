/***************************************************************************
 *   Copyright (C) 2008 by Tick                                            *
 *   noden@sol.dk                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/*	This is a very simple IRC client bot. It doesnt do much and need a lot of error handeling and stuff.
   It doesnt handle everything the IRC RFCs require to be fully valid.
   Use it as is, to se how the basic is and IRC client is. Nothing more.
   This has some design flaws. It doesnt reconnect if accidently disconected from network issues.
   If one function hangs, the whole bot hangs. If it hangs too long, the bot will miss the PING and will be kicked from the server for not responding to this. The RFC says around every 5 seconds or so if I remember correctly.
   Read the RFC. And feel free to mess with this source if you like.
   I am most likely not going to improve this. I just wanted to try it out.
   I tried to leave as many comments in the code as I could.
	Some of the code was done as temporary and is not proper code but I never got to fixing it.
	
	Downloaded at http://kingscradle.spaces.live.com/ from SkyDrive.

	Commands supported:
	!end - Log off the bot and exit.
	!restart - Log off the bot and restart it. 
	!hello - Message to the bot that make the bot respond. An easy way of testing if the bot is responding.
	!osversion - A private message to the bot. The bot will reply with the OS information of the host it is running on.
*/

/* May 15 - 2010: removed remporary code.
	Just a cleanup of functions not available in this public version
	By Tick. */

/* Preprocessor directives and includes */

#include <iostream>			// for the STL string
#include <cstdlib>			// For EXIT_SUCCESS, system(), exit(), srand() etc.
#include <cstring>			// For memset(), strlen(), strerror etc.
#include <errno.h>			// For errno in the bail() function
#include <arpa/inet.h>		// For inet_addr, servaddr, AF_INET, htons(), PF_INET, socket()
//#include <time.h>			// For time() which I dont think I use yet
#include <sys/utsname.h>	// For struct utsname
#include "ircbot.h"			// Our own header file where we put all the memberfunctions, structs etc.
#include <fstream>
#include <time.h> //do obsługi funkcji czasowych

using namespace std;		// Just use the standard namespace

int main(int argc, char *argv[])		// Main program
	{
	forkdaemon();							// Call this function to have the bot run as a daemon
	class ircbot * iPTR = new ircbot;		// Create and allocate a new instance of the main class ircbot
	string work;							// Create the string "work" to use in loop to handle messages
	work.reserve(MAX_MESSAGE_SIZE);			// Reserve 512 bytes for messages RFC say this is max
	bool loopme = true;						// true/false handler to let us leave loop when needed
	string path = "irclog/";
	time_t currTime;            // bieżący czas
	struct tm *timeinfo;    //struktura danych czasowych
	char datetime[16];
	time(&currTime);  //odczytanie bieżącego czasu
	timeinfo = gmtime(&currTime);
	struct tm oldTimeInfo = *timeinfo;

	strftime(datetime,11,"%Y-%m-%d",timeinfo);   //skopiowanie do zmienej datetime stringu z czasem "YYMMDD_hh-mm-ss"

	std::string ircfilename = path + datetime + ".txt";
	ofstream ircfile;
	ircfile.open(ircfilename.c_str(), ios::out | ios::app);
	if (ircfile.fail())
		{
			cout << "nie można otworzyć pliku wyjściowego "<< ircfilename.c_str() << endl;
			exit(1);
		}
	while (loopme)						// This is the main loop
		{
			time(&currTime);
			timeinfo = gmtime(&currTime);
			if (timeinfo->tm_mday > oldTimeInfo.tm_mday || (timeinfo->tm_mday == 1 && oldTimeInfo.tm_mday >27))
			{
				ircfile.close();
				strftime(datetime,11,"%Y-%m-%d",timeinfo);
				ircfilename = path + datetime + ".txt";
				ircfile.open(ircfilename.c_str(), ios::out | ios::app);
				if (ircfile.fail())
					{
						cout << "nie można otworzyć pliku wyjściowego "<< ircfilename.c_str() << endl;
						exit(1);
					}
			}
			strftime(datetime,11,"[%H:%M:%S]",timeinfo);

		work.clear();					// Empty the STL string "work" to make sure it is empty
		work = iPTR->readmess();	// Read stuff form the IRC server
		work.reserve();				// Truncate the work string to the size of what was read
		
		if (!(work.find("PING :") == std::string::npos)) iPTR->sendpong();		// Did we receive a PING from IRC server? Send PONG back
		if (!(work.find(":!hello") == std::string::npos)) iPTR->privmsg("Hi there!");		// Did we receive a hello? reply...
		
		/* Keep an eye on private messages */
		if (!(work.find(iPTR->myself()) == std::string::npos))		// Look for messages containing this bot name.
			{
				cout << "for me:" << work;
			if (!(work.find("!osversion") == std::string::npos)) iPTR->osversion();	// If this private message is for me, was I asked for osversion?
			if (!(work.find(":cezaryece!") == std::string::npos))
				{
				if (!(work.find(":!end") == std::string::npos)) // Look for ":!end" and if we find it, exit loop
					{
					ircfile.close();
					break;
					}
				if (!(work.find(":!restart") == std::string::npos))		// Look for restart command. Start a new bot and exit old one
					{
					ircfile.close();
					system("./ircbot");		// Start a new bot
					break;							// And exit the loop to stop the old one. This is an odd way of doing this
					}
				}
			}
		else if (!(work.find("PRIVMSG #scribus") == std::string::npos))
			{
				size_t x, y;
				string PRV = " PRIVMSG #scribus ";
				x = work.find_first_of('~');
				y = work.find_first_of(' ',x) + PRV.length();
				work.erase(x,y-x);
				ircfile << datetime << work;
				ircfile.flush();
			}
		}
	if (ircfile.is_open()) ircfile.close();
	delete iPTR;			// Delete the alocated main class ircbot. iPTR is a pointer this this class
	return EXIT_SUCCESS;	// Return 0 to OS and exit nicely
	}
