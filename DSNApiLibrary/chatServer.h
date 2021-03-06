/*
The ChatServer watches for new connections and
connect to them.
*/

#ifndef chatServer_h
#define chatServer_h

#ifdef _WIN32
 #include <stdio.h>
 #include <winsock2.h>
 #include <stdlib.h>
#elif __linux__
 #include <stdio.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <netinet/in.h>
#endif

#include <thread>
#include <mutex>
#include <string.h>
#include <list>
#include "chat.h"

#define BUFFSIZE 128
#define HOSTSOCK 8000	 // Hope that it isn't being used. Needs researching.

// No one talks to more than a 100 people at once... right?
#define MAXCONNECT 100

class ChatServer{
public:
	/*
	Constructor
	Purpose: To setup a connection with a chatServer object.
	Returns: NA
	*/
	ChatServer();
	/*
	serverLoop
	Purpose: To constantly poll for new connections.
	Returns: NA
	*/
	virtual void serverLoop();
	/*
	stopServer
	Purpose: To let the serverLoop exit.
	Returns: NA
	*/
	virtual void stopServer();
	/*
	stopServer
	Purpose: A getter function for the bool running
	Returns: running
	*/
	virtual bool serverRunning(); // Is the server running?
	/*
	getCurrent
	Purpose: Gets current connection.
	Returns: NA
	*/
	virtual bool checkCurrent();
	/*
	getClient
	Purpose: Gets the next Chat object
	Returns: NA
	*/
	virtual Chat* getClient();

	/*
	Destructor
	Purpose: To safely destroy the chat object
	Returns: NA
	*/
	~ChatServer();
private:
	std::mutex rLock;						// Lock for running.
	bool running;							// Is the Host running?
	struct sockaddr_in server, client;		// socket info
	int serverSock,clientSockInit;

	Chat* clients[MAXCONNECT];				//
	bool sConnected[MAXCONNECT];			// If the socket is connected client
	int current;// Current connection number
	int lastUpdated;
};




#endif
