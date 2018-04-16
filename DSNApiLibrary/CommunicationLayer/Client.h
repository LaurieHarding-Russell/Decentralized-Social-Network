/* 
The Client Class is meant to initiate a connection with a Client server.
Once a connection is established, the Client object sends and recieves 
Data with the Client Server.
*/

#ifndef Client_h
#define Client_h

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
#define HOSTSOCK 8000	 // This is the default socket being used by the ClientServer.

// FIXME, Think about where to put this. Maybe in some sort of util file?
enum class ConnectionState { NotInitialized, ConnectionFailed, OK, messageFailedToSend};

bool ConnectonStateConnected(ConnectionState value) {
	return ConnectionState::NotInitialized != value || ConnectionState::ConnectionFailed != value;
}

class Client{
 public:
	/*
	Constructor
	Purpose: To setup a connection with a ClientServer object using an address
	Returns: NA
	*/
	Client(std::string address);

	/*
	Constructor
	Purpose: To accept a connection with a ClientServer object using an existing socket
	Returns: NA
	*/
	Client(int socket,std::string address);

	/*
	Destructor
	Purpose: To safely destroy the Client object
	Returns: NA
	*/
	~Client();
	
	/*
	sendMessage
	Purpose: To safely destroy the Client object
	Returns: Current failedState.
	*/
	virtual ConnectionState sendMessage(std::string message);
	
	/*
	messageCheckLoop
	Purpose: To constantly poll for new messeges.
	Returns: NA
	Note: Any commands that need to be processed in this loop should start with
	the prefix ~/
	*/
	virtual void messageCheckLoop();
	
	/*
	getState
	Purpose: to get the value of failedState
	Returns: failedState
	*/
	virtual ConnectionState getState();
	
	/*
	getMessage
	Purpose: to get the value of message and clear it.
	Returns: message
	*/
	virtual std::string getMessage();
	
	/*
	endMessageCheckLoop
	Purpose: To let the messageCheckLoop exit.
	Returns: NA
	*/
	virtual void endMessageCheckLoop();

private:
	// Sock Stuff
	 struct sockaddr_in client;
	 std::string address;		// IP address of user we are connecting to.
	 int sock;					// The connecting Socket

	 ConnectionState failedState;
	 std::mutex rLock;			// lock for failedState
	 // Message stuff
	 std::mutex messageLock;	// Locks the message string
	 std::string message;		// Stores the recieved messages.
};

#endif
