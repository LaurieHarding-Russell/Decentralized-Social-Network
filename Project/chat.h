/* 
The Chat Class is meant to initiate a connection with a chat server.
Once a connection is established, the chat object sends and recieves 
Data with the Chat Server.
*/

#ifndef chat_h
#define chat_h

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

#include <mutex>
#include <string.h>

#define BUFFSIZE 128
#define HOSTSOCK 8000	 // This is the default socket being used by the chatServer.

class Chat{
 public:
	/*
	Constructor
	Purpose: To setup a connection with a chatServer object using an address
	Returns: NA
	*/
	Chat(std::string address);

	/*
	Constructor
	Purpose: To accept a connection with a chatServer object using an existing socket
	Returns: NA
	*/
	Chat(int socket,std::string address);

	/*
	Destructor
	Purpose: To safely destroy the chat object
	Returns: NA
	*/
	~Chat();
	
	/*
	sendMessage
	Purpose: To safely destroy the chat object
	Returns: Current failedState value.
	*/
	int sendMessage(std::string message);
	
	/*
	messageCheckLoop
	Purpose: To constantly poll for new messeges.
	Returns: NA
	Note: Any commands that need to be processed in this loop should start with
	the prefix ~/
	*/
	void messageCheckLoop();
	
	/*
	getState
	Purpose: to get the value of failedState
	Returns: failedState
	*/
	int getState();
	
	/*
	getMessage
	Purpose: to get the value of message and clear it.
	Returns: message
	*/
	std::string getMessage();
	
	/*
	endMessageCheckLoop
	Purpose: To let the messageCheckLoop exit.
	Returns: NA
	*/
	void endMessageCheckLoop();

private:
	// Sock Stuff
	 struct sockaddr_in client;
	 std::string address;		// IP address of user we are connecting to.
	 int sock;					// The connecting Socket
	 /*
	 failedState Values
	 0:The constructor failed to create 
	 1: Connection Failed
	 20: Everythings working.
	 30: Last message sent failed to send all of its bytes
	 Note: New Fatal errors should be bellow 20.
	 */
	 int failedState;
	 std::mutex rLock;			// lock for failedState
	 // Message stuff
	 std::mutex messageLock;	// Locks the message string
	 std::string message;		// Stores the recieved messages.
};

#endif
