/* chat.cpp
Client
*/

#include "chat.h"
#include <iostream>
/* Currently not being used... */
Chat::Chat(){

}

/*
Connect to host (You are the client)
address, name
*/
Chat::Chat(std::string a, std::string n){
	address =a;	// Saveing the address!
	name = n;
	failedState= 0;
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) != -1) { // Creating TCP socket
		failedState =1;
		memset(&client, 0, sizeof(client));
		client.sin_family = AF_INET;									// Type=Internet/IP
		client.sin_addr.s_addr = inet_addr(address.c_str());	//	IP address 
		client.sin_port = htons(HOSTSOCK);						// server port 
		if (connect(sock,(struct sockaddr *) &client,sizeof(client)) != -1) { // Try to connect
			failedState =20; // We are connected! I think...
		}else{
			perror("socket Error"); // For testing
		}
		//TO DO: Ask for name to confirm right person. Don't sniff me.

	}	
}
/*Returns number of bytes that got through */
int Chat::sendMessage(std::string message){ 
	float good;
	rLock.lock();
	if(failedState>=20){ // Fatal errors are bellow 20... (ex. failed to connect equals 0 or 1)
		if (good =send(sock, message.c_str(), message.length(), 0) != message.length()){
			failedState == 30; // Fenrir's teeth! Message failed to send all bytes.
		}
	}
	good = failedState;
	rLock.unlock();
	return (good/message.length()); // Everything is good. 
}

/* 
The main gives this a thread to constantly check for new messages 
*/
void Chat::messageCheckLoop(){
	char buffer[BUFFSIZE];
	int size;
	rLock.lock();
	while(failedState>=20){
		rLock.unlock();
		if((size=recv(sock, buffer, BUFFSIZE-1, 0)) < 1) {
			// No new bytes...

		}else{ // NEW STUFF!
			if(strcmp(buffer, "~/exit")){ // On exit.
				failedState==1;
			}
			messageLock.lock();
			message =message +buffer;
			messageLock.unlock();
		}
		rLock.lock();
	}
	rLock.unlock();
}

/*Get failedState*/
int Chat::getState(){
	int temp;
	rLock.lock();
	temp = failedState;
	rLock.unlock();
	return temp;
}

/* Get the message for output */
std::string Chat::getMessage(){
	std::string returnS;

	messageLock.lock();
	returnS= message; // get message
	message =""; // clear message;
	messageLock.unlock();

	return returnS;
}

// IMPORTANT! Don't forget! Don't even think to forget. If you forget it lives.
void Chat::endMessageCheckLoop(){
	rLock.lock();
	failedState =0; // End it.
	rLock.unlock();
}
/*

*/
Chat::~Chat(){
	#ifdef _WIN32
	closesocket(sock);
	#elif __linux__
	close(sock);	// Disconnect
	#endif
}
