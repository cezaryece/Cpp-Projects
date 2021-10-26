/***************************************************************************
 *   Copyright (C) 2008 by Tick   *
 *   tick@testbox   *
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

#include <stdio.h>
using namespace std;

/* Globals */

string CRLF = "\r\n";	// Carriage return, Line Feed
pid_t PID;					//  Container for process ID

		
/* Preprocessors set according to RFC */

#ifndef MAX_MESSAGE_SIZE
#define MAX_MESSAGE_SIZE 512
#endif

#ifndef MAX_NICK_SIZE
#define MAX_NICK_SIZE 10
#endif


/* Prototypes */
static void bail(const char *on_what);		// This is here so the functions that call this before this is defined, knows it 
void forkdaemon(void);

/* Classes and structs */
class ircbot
	{
	private:
		char prefix;			// IRC command prefix
		int servsockd;			// Socket descriptor used to connect to IRC
		int servport;			// Port for IRC server
		int bytesread;			// Returncode from read
		int written;			// Returncode from write
		string servIP;			// Buffer for IRC server IP
		struct sockaddr_in servaddr;	// Address struct for IRC connection
		string nick;			//	Buffer for the irc nick. RFC 2812 says max 9 chars
		char readbuf[MAX_MESSAGE_SIZE];	// Readbuffer. RFC 2812 says max 512 chars including CRLF
		char writebuf[MAX_MESSAGE_SIZE];	// Writebuffer
		string channel;		// string containing channel
		string password;		// Password for bot to connect ti IRC server with
		string realname;		// Real name
		string privateme;		// Buffer for catching private messages ":<nick> !"
	protected:
		void connectirc(void);	// Create connection and connect it
		void disconnirc(void);	// Close connection to IRC server
		void loginpass(void);	// Register IRC session by sending PASS
		void setuser(void);		// Set IRC user
		void joinchannel(string);	// Join channel on IRC server
		void changenick(void);	// Change the IRC bot nick
		void quit(string);			// Send quit to server
		void randomnick(void);	// Generate random nick
	public:
		ircbot(void);				// Constructor
		~ircbot(void);				// Deconstructor
		string readmess(void);	// Used to read junk from socket
		void privmsg(string);	// Send a chat message to IRC server
		void sendpong(void);		// Reply to server PING
		string myself(void);		// Dummy function to seperate public and private messages
		void osversion(void);	// Find os version
	};


/* Class member functions */

void ircbot::osversion(void)		// This sends the client OS version to the one that request it.
	{
	struct utsname myname;		// Struct for OS information
	if (uname(&myname))			// Have the OS fill in the myname class
		{
		privmsg("Error fetching OS info.");
		}
	else
		{
		string sysname = myname.sysname;			// Store values from the myname struct in STL strings
		string nodename = myname.nodename;
		string release = myname.release;
		string version = myname.version;
		string machine = myname.machine;
		string tempos = "I am a \"" + sysname + "-box\" running \"" + release + "\" compiled at \"" + version;
		tempos += "\" @ \"" + nodename + "\" with architechture \"" + machine + "\"...";	// concat everything together
		privmsg(tempos);		// Send the info as a private message
		}
	}

string ircbot::myself(void)
	{
	return privateme;		// Return the content of the string private me. Buffer used for catching private messages
	}

void ircbot::randomnick(void)		// This function generates a random nick. Might do dublicates if many bots are on.
	{
	/*char tempnick[MAX_NICK_SIZE];		// Buffer for generating nick
	srand(time(0));						// Init random generator
	
	for (int i = 0; i < (MAX_NICK_SIZE - 1); i++)	// Loop
		{
		int high = 122, low = 97;				// Find anything between a and z in lowercase
		tempnick[i] = (rand() % (high - low + 1) + low);		// Find a random letter and store it. One by one.
		}
	tempnick[MAX_NICK_SIZE - 1] = '\0';*/		// Terminate array of chars and make it a c-style string
	char tempnick[10] = "CezEceBot";
	privateme = tempnick;						// Store the newly generated nick in a STL string
	privateme = " PRIVMSG " + privateme;		// Add the ":!" to the nick so we know it is a private message
	
	nick = tempnick;					// Store it as a STL string
	password = tempnick;				// Use nick as password also
	realname = tempnick;				// Use nick as real name also
	}

void ircbot::sendpong(void)	// This function make and send the PONG reply to the IRC PING request. RFC stuff.
	{
	string pong = "PONG" + CRLF;					// PONG message. Reply to PING
	memset(&writebuf, 0, sizeof writebuf);		// Clean up write buffer
	pong.copy(writebuf, sizeof writebuf);		// Copy the pong from a STL string to an old c-style string to use with write()
	
	written = write(servsockd, writebuf, strlen(writebuf));	// Send PING reply to IRC server
	if (written == -1) bail("write()");		// WOW.. Hello. Errorhandling is actually present.
	}

void ircbot::privmsg(string mesg)	// This function is used to send private messages with
	{
	mesg = "PRIVMSG #" + channel + " :" + mesg + CRLF;		// Concat everything to apply to RFC syntax
	memset(&writebuf, 0, sizeof writebuf);		// Clean up write buffer
	mesg.copy(writebuf, sizeof writebuf);		// Copy the private message from STL string to c-style string
	
	written = write(servsockd, writebuf, strlen(writebuf));	// Send message (Server should not reply)
	if (written == -1) bail("write()");
	}

void ircbot::quit(string qmesg)	// This function makes this IRC client send the QUIT message to logoff from IRC server
	{
	qmesg = "QUIT :" + qmesg + CRLF;		// Put together the full command
	memset(&writebuf, 0, sizeof writebuf);		// Clean up write buffer
	qmesg.copy(writebuf, sizeof writebuf);		// Copy the STL string to a c-style string to use with write
	
	written = write(servsockd, writebuf, strlen(writebuf));	// Send quit command
	if (written == -1) bail("write()");
	}

void ircbot::changenick(void)		// This function tell the IRC server what NICK to use. This is randomly generated
	{
	nick = "NICK " + nick + CRLF;				// Combine nick command and nick
	memset(&writebuf, 0, sizeof writebuf);		// Clean writebuffer
	nick.copy(writebuf, sizeof writebuf);		// Copy STL string to old style c-string
	
	written = write(servsockd, writebuf, strlen(writebuf));	// Send nick command
	if (written == -1) bail("write()");
	}

void ircbot::joinchannel(string chn)	// This function tell the IRC server which chanel to join
	{
	chn = "JOIN #" + channel + CRLF;			// Combine channelname and join command
	memset(&writebuf, 0, sizeof writebuf);			// Clean writebuffer
	chn.copy(writebuf, sizeof writebuf);		// Copy STL string to old c-stryle string
	
	written = write(servsockd, writebuf, strlen(writebuf));	// Send join command
	if (written == -1) bail("write()");
	}

void ircbot::setuser(void)		// Tell the IRC server what user to use.
	{
	realname = "USER guest 0 * :" +realname + CRLF;		// Combine USER and realname
	memset(&writebuf, 0, sizeof writebuf);					// Clean up write buffer
	realname.copy(writebuf, sizeof writebuf);
	
	written = write(servsockd, writebuf, strlen(writebuf));	// Send USER command
	if (written == -1) bail("write()");
	}


void ircbot::loginpass(void)		// Send the password to the IRC server. This is actually the same as the nick
	{
	password = "PASS " + password + CRLF;		// Combine PASS and password
	memset(&writebuf, 0, sizeof writebuf);		// Clean up write buffer
	password.copy(writebuf, sizeof writebuf);
	
	written = write(servsockd, writebuf, strlen(writebuf));	// Send pass command
	if (written == -1) bail("write()");
	}

string ircbot::readmess(void)		// This read everything from the IRC server. This is called in the main loop
	{
	memset(&readbuf, 0, sizeof readbuf);		// Empty the read buffer to avoid reading old stuff.
	bytesread = read(servsockd, readbuf, sizeof readbuf - 1);	// Read from socket
	if (bytesread == -1) bail("read()");
	
	string messmanip = readbuf;	// Copy the c-style string to a STL string for easy manipulation
	return messmanip;		// Return the message to caller
	}

void ircbot::connectirc(void)		// This function does the actual socket stuff.
	{
	int success = 0;	// This is a buffer for error handling. The errorhandeling present anyway
	servaddr.sin_family = AF_INET;		// Set type to Internet protocol
	servaddr.sin_addr.s_addr = inet_addr(servIP.c_str());		// Store the server IP
	servaddr.sin_port = htons(servport);		// Store the port number in network order. Debian GNU is little endian, but still.
	
	servsockd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	// Create a TCP socket. PF_INET AND AF_INET are the same.
	if (servsockd == -1) bail("socket()");

	success = connect(servsockd, (const sockaddr *)&servaddr, sizeof servaddr);	// Connect socket to IRC
	if (success == -1) bail("connect()");
	randomnick();		// Call function to generate a random nick
	realname = "EceBot";
	loginpass();		// Call function to send the password to IRC server
	changenick();		// Call function to send the nick to the IRC server
	setuser();			// Call function to send user type
	joinchannel(channel);		// Call function to join a channel
	privmsg("Joining in...");	// Send a chat message so we can see the bot join the channel
	}

void ircbot::disconnirc(void)		// This function is called when the bot is logging out
	{
	quit("Leaving game...");		// Send quit to IRC server and a logoff message
	sleep(1);					// Sleep one second to make sure we dont hang on IRC server.
	close(servsockd);			// Close socket (descriptor) and perform 4-way termination shake
	}

/* Constructor and deconstructor */
ircbot::ircbot()	// This constructor is called when the main class is created
	{
	servport = 8001;			// Hardcoded portnumber. The default one
	servIP = "82.96.64.4";	// The IRC server ip. Also hardcoded. You might wanna change this. Should support FQDNs
	channel = "scribus";			// This is the channel to join
	connectirc();				// Call function to connect to IRC
	}

ircbot::~ircbot()				// This function is called when the main class is deleted. Was created with "new"
	{
	disconnirc();		// Call function that send QUIT message to IRC server
	}

/* Functions */

static void bail(const char *on_what)	// Function by Warren Q. Gay @ St. Catharines, Ontario, Canada
    {												// This function is used to print out messages when we use EXIT. Something went wrong.
    if (errno!=0)		// If errno is set, print out the message.
        {
        fputs(strerror(errno), stderr);
        fputs(": ", stderr);
        }
    fputs(on_what, stderr);	// Print out error message returned from function
    fputc('\n', stderr);		// Newline.. c-style ..
    exit(1);		// Exit in error and tell the OS we did it.
    }

void forkdaemon(void)	// This function forks a child and kills the parent, making this a daemon. Might catch a bad signal this way.
	{
   if ((PID = fork()) == -1) bail("fork()");   // Fork a new process
   else if (PID > 0) exit(0);		// If I am parent the exit nicely
   setsid();							// Run process in new session
	}









