/*
Holds all the data for Chat server functions.
I will probably make this into a static class since I don't see 
a reason for haveing multiple instances of the host module.

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

#include <thread>	// Not supported in windows... maybe.
#include <mutex>
#include <string.h>
#include <list>
#define BUFFSIZE 128
#define HOSTSOCK 8000	 // Hope that it isn't being used. Needs researching.

// No one talks to more than a 100 people at once... right?
#define MAXCONNECT 100
/*struct message{
	std::thread threadId;
	int clientSock;
	std::string messages;
	std::mutex messageLock;
	bool sConnected;
};*/

class ChatServer{
public:
	ChatServer();
	void serverLoop();
	void stopServer();
	bool serverRunning(); // Is the server running?
	bool socketConnected(int id);
	std::string getMessages(int id);
	int sendMessage(int id,std::string message);
	~ChatServer();
private:
	std::mutex rLock; // Locks running. 
	bool running;		 // Is the Host running?	
	void handleClient(int sock, int me); // threaded
	struct sockaddr_in server, client;
	int serverSock,clientSockInit;
	std::thread threadIds[MAXCONNECT];	 // One thread per conversation
	int clientSock[MAXCONNECT];
	std::string messages[MAXCONNECT];
	std::mutex messageLock[MAXCONNECT];
	bool sConnected[MAXCONNECT]; // If the socket is connected client
	//std::list<message> connections;	// Or vector... Will have to think about this... 
	int current;// Current connection number
};




#endif
