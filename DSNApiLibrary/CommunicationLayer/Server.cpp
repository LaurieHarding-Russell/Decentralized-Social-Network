#include "Server.h"

Server::Server(){
	current = 0;
	lastUpdated = 0;
}

void Server::serverLoop(){
	struct timeval timeIntervalBetweenAccepts; // Polling
	fd_set readfds;
	timeIntervalBetweenAccepts.tv_sec = 0;
	timeIntervalBetweenAccepts.tv_usec = 0;
	fd_set serverSocket; // New Socket File Description.
	acceptMessagesLock.lock();
	acceptMessages = true;
	acceptMessagesLock.unlock();
	if ((serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) >= 0) {
		memset(&server, 0, sizeof(server));			// Clear struct 
		server.sin_family = AF_INET;				// Internet/IP 
		server.sin_addr.s_addr = htonl(INADDR_ANY);	// Incoming addr 
		server.sin_port = htons(HOSTSOCK); 			// server port 
		if (bind(serverSock, (struct sockaddr *) &server,sizeof(server) ) >= 0) {
			// Listen on the server socket
			if (listen(serverSock, MAXCONNECT) >= 0) {
				FD_ZERO(&serverSocket);// clear thet socket
				FD_SET(serverSock,&serverSocket);// Add server socket to set
				acceptMessagesLock.lock();
				while(acceptMessages){	
					acceptMessagesLock.unlock();
					#ifdef _WIN32 // Stupid win sockets...
					int clientlen = sizeof(client);
					#elif __linux__
					unsigned int clientlen = sizeof(client);
					#endif
					if(select(1, &serverSocket, NULL, NULL, &timeIntervalBetweenAccepts)){  // accept will accept... won't block. 
						if ((clientSockInit = accept(serverSock, (struct sockaddr *)&client,&clientlen)) >= 0){ // Grabing client info
							inet_ntoa(client.sin_addr);
							clients[current] = new Client(clientSockInit,"");
							current++; 
						}
					}
				}
				acceptMessagesLock.unlock();
			}
		}
	}
	#ifdef _WIN32
		closesocket(serverSock);
	#elif __linux__
		close(serverSock);
	#endif
}

void Server::stopServer(){
	acceptMessagesLock.lock();
	acceptMessages = false;
	#ifdef _WIN32
		closesocket(serverSock);
	#endif
	acceptMessagesLock.unlock();
}

bool Server::serverRunning(){
	acceptMessagesLock.lock();
	bool acceptMessagesCopy = acceptMessages;
	acceptMessagesLock.unlock();
	return acceptMessagesCopy;

}

bool Server::checkCurrent(){
	return current==lastUpdated;
}

Client* Server::getClient(){
	lastUpdated++;
	return clients[lastUpdated-1];
}

Server::~Server(){
	for(int lpC=lastUpdated;lpC!=current;lpC++){
		delete clients[lpC];
	}
}
