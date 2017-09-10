#include "chatServer.h"

ChatServer::ChatServer(){
	current =0; // current number of connections
	lastUpdated=0;
}

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
							clients[current] = new Chat(clientSockInit,"");
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

bool ChatServer::serverRunning(){
	bool temp;
	rLock.lock();
	temp = running;
	rLock.unlock();
	return temp;
}
bool ChatServer::checkCurrent(){
	return current==lastUpdated;
}

Chat* ChatServer::getClient(){
	lastUpdated++;
	return clients[lastUpdated-1];
}

ChatServer::~ChatServer(){
	for(int lpC=lastUpdated;lpC!=current;lpC++){
		delete clients[lpC];
	}
}
