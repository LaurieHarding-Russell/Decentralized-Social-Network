/* 
Client.cpp 
*/
#include "Client.h"


Client::Client(std::string a){
	address =a;
	failedState= ConnectionState::NotInitialized;																// If everything works failedState will chage to 20.
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) != -1) {				// Creating TCP socket
		failedState =ConnectionState::ConnectionFailed;															// Not connected yet.
		memset(&client, 0, sizeof(client));	
		client.sin_family = AF_INET;											// Type=Internet/IP
		client.sin_addr.s_addr = inet_addr(address.c_str());					//	IP address 
		client.sin_port = htons(HOSTSOCK);										// server port 
		if (connect(sock,(struct sockaddr *) &client,sizeof(client)) != -1) {	// Try to connect
			failedState = ConnectionState::OK;
		}
	}	
}

Client::Client(int socket,std::string a){
	address =a;
	sock=socket;
	failedState =ConnectionState::OK;
}

ConnectionState Client::sendMessage(std::string message){ 
	rLock.lock();
	if(ConnectonStateConnected(failedState)){
		if (send(sock, message.c_str(), message.length(), 0) != message.length()){
			failedState == ConnectionState::messageFailedToSend;
		}
	}
	ConnectionState returnFS= failedState;
	rLock.unlock();
	return returnFS; 
}

void Client::messageCheckLoop(){
	char buffer[BUFFSIZE];
	int size;
	rLock.lock();
	while(!ConnectonStateConnected(failedState)){
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

ConnectionState Client::getState(){
	ConnectionState temp;
	rLock.lock();
	temp = failedState;
	rLock.unlock();
	return temp;
}

std::string Client::getMessage(){
	std::string returnS;
	messageLock.lock();
	returnS= message;	// get message
	message ="";		// clear message;
	messageLock.unlock();
	return returnS;
}

void Client::endMessageCheckLoop(){
	rLock.lock();
	failedState = ConnectionState::NotInitialized;
	rLock.unlock();
}

Client::~Client(){
	#ifdef _WIN32
	closesocket(sock);
	#elif __linux__
	close(sock);
	#endif
}
