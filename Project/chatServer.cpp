/* chatServer.cpp*/

#include "chatServer.h"
#include <iostream>
/* There can only be one! Well, there should only be one. This allows other computers to connect.*/
ChatServer::ChatServer(){
	current =0; // current number of connections
}
/*
The function polls a single sockets recieved data.
*/
void ChatServer::handleClient(int sock, int me) {
	char buffer[BUFFSIZE];
	sConnected[me] =true;
	int size=0;
	rLock.lock();
	while(sConnected[me]&&running){ // Runs while server is running and client connected.
		rLock.unlock();
		if ((size = recv(sock, buffer, BUFFSIZE, 0)) > 0) { // Check for data
			messageLock[me].lock();
			messages[me]= messages[me]+buffer; // Put in buffer.
			messageLock[me].unlock();
		}
		rLock.lock();
	}
	rLock.unlock();
#ifdef _WIN32
	closesocket(sock);
#elif __linux__
	close(sock);	// Disconnect
#endif
}
/*socket connected getter.*/
bool ChatServer::socketConnected(int id){
	return sConnected[id];
}
/* Get Message */
std::string ChatServer::getMessages(int id){
	std::string getM;
	messageLock[id].lock();
	getM = messages[id];
	messages[id]="";
	messageLock[id].unlock();
	return getM;
}

/*
 Send Message.
Returns number of bytes sent.
*/
int ChatServer::sendMessage(int id, std::string message){
	return (send(clientSock[id], message.c_str(), message.length(), 0));
}
/* 
Server Host that clients initially connect too.
*/
void ChatServer::serverLoop(){
	// time interval to wait for accepts. Polling so don't wait.
	struct timeval tv;
	fd_set readfds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	fd_set nSFD; // New Socket File Description.
	rLock.lock();
	running = true;
	rLock.unlock();
	if ((serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) >= 0) {
		memset(&server, 0, sizeof(server));					 // Clear struct 
		server.sin_family = AF_INET;									// Internet/IP 
		server.sin_addr.s_addr = htonl(INADDR_ANY);	 // Incoming addr 
		server.sin_port = htons(HOSTSOCK);						// server port 
		if (bind(serverSock, (struct sockaddr *) &server,sizeof(server) ) >= 0) {
			// Listen on the server socket
			if (listen(serverSock, MAXCONNECT) >= 0) {
				rLock.lock();
				FD_ZERO(&nSFD);// clear thet socket
				FD_SET(serverSock,&nSFD);// Add server socket to set
				while(running){
				    rLock.unlock();		
					
					#ifdef _WIN32 // Stupid win sockets...
					int clientlen = sizeof(client);
					#elif __linux__
					unsigned int clientlen = sizeof(client);
					#endif
					if(select(1,&nSFD,NULL,NULL,&tv)){  // accept will accept... won't block. 
						if ((clientSockInit = accept(serverSock, (struct sockaddr *)&client,&clientlen)) >= 0){ // Grabing client info
							inet_ntoa(client.sin_addr);
							threadIds[current] = std::thread(&ChatServer::handleClient,this,clientSockInit, current); // Start socket polling thread
							clientSock[current] = clientSockInit; // Sockets handle.
							current++; 
						}
					}
					rLock.lock();
				}
				rLock.unlock();
			}
		}
	}
	#ifdef _WIN32
		closesocket(serverSock);
	#elif __linux__
		close(serverSock);	// Disconnect
	#endif
	for(int lp1 =0; lp1!=current;lp1++){
		threadIds[lp1].join();
	}
}

void ChatServer::stopServer(){
	rLock.lock();
	running = false;
	// Stop the accept command by closeing the serverSock on windows.
	// Not very pretty... but it works
	#ifdef _WIN32
		closesocket(serverSock);
	#endif
	rLock.unlock();
}
/* Returns true if server is still running */
bool ChatServer::serverRunning(){
	bool temp;
	rLock.lock();
	temp = running;
	rLock.unlock();
	return temp;
}

ChatServer::~ChatServer(){
	// delete [] threadIds; // glib error
}
