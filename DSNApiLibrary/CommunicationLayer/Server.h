/*
The Server watches for new connections and
connect to them.
*/

#ifndef Server_h
#define Server_h

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
#include "Client.h"

#define BUFFSIZE 128
#define HOSTSOCK 8000

// FIXME
#define MAXCONNECT 100

class Server{
public:
	/*
	Constructor
	Purpose: To setup a connection with a Server object.
	Returns: NA
	*/
	Server();
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
	Purpose: Gets the next Client object
	Returns: NA
	*/
	virtual Client* getClient();

	/*
	Destructor
	Purpose: To safely destroy the Client object
	Returns: NA
	*/
	~Server();
private:
	//FIXME, Can't get atomic to work. Incomplete type. going back to locking.
	std::mutex acceptMessagesLock;
	bool acceptMessages;		// Is the Host running?
	struct sockaddr_in server, client;		// socket info
	int serverSock,clientSockInit;

	Client* clients[MAXCONNECT];
	bool sConnected[MAXCONNECT];			// If the socket is connected client
	int current;// Current connection number
	int lastUpdated;
};




#endif
