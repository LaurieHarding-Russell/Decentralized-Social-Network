/* 
Chat.cpp 
*/
#include "chat.h"

Chat::Chat(std::string a){
	address =a;
	failedState= 0;																// If everything works failedState will chage to 20.
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) != -1) {				// Creating TCP socket
		failedState =1;															// Not connected yet.
		memset(&client, 0, sizeof(client));	
		client.sin_family = AF_INET;											// Type=Internet/IP
		client.sin_addr.s_addr = inet_addr(address.c_str());					//	IP address 
		client.sin_port = htons(HOSTSOCK);										// server port 
		if (connect(sock,(struct sockaddr *) &client,sizeof(client)) != -1) {	// Try to connect
			failedState =20;	// We are connected!
		}else{
			perror("socket Error"); // For testing. Failed to connect.
		}
	}	
}

Chat::Chat(int socket,std::string a){
	address =a;
	sock=socket;
	failedState =20;
}

int Chat::sendMessage(std::string message){ 
	rLock.lock();
	if(failedState>=20){		// Fatal errors are bellow 20.
		if (send(sock, message.c_str(), message.length(), 0) != message.length()){
			failedState == 30;	//  Message failed to send all bytes.
		}
	}
	int returnFS= failedState;
	rLock.unlock();
	return returnFS; 
}

void Chat::messageCheckLoop(){
	char buffer[BUFFSIZE];
	int size;
	rLock.lock();
	while(failedState>=20){
		rLock.unlock();
		if((size=recv(sock, buffer, BUFFSIZE-1, 0)) >= 1) { // Check for new bytes
			messageLock.lock();
			message =message +buffer;
			messageLock.unlock();
		}
		rLock.lock();
	}
	rLock.unlock();
}

int Chat::getState(){
	int temp;
	rLock.lock();
	temp = failedState;
	rLock.unlock();
	return temp;
}

std::string Chat::getMessage(){
	std::string returnS;
	messageLock.lock();
	returnS= message;	// get message
	message ="";		// clear message;
	messageLock.unlock();
	return returnS;
}

void Chat::endMessageCheckLoop(){
	rLock.lock();
	failedState =0; // End it.
	rLock.unlock();
}

Chat::~Chat(){
	#ifdef _WIN32
	closesocket(sock);
	#elif __linux__
	close(sock);	// Disconnect
	#endif
}
