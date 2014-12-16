/* chatServer.cpp*/

#include "chatServer.h"

/* There can only be one! Well, there should only be one. This allows other computers to connect.*/
ChatServer::ChatServer(){
  current =0;
}
/*

*/
void ChatServer::handleClient(int sock, int me) {
  char buffer[BUFFSIZE];
  bool loop =true;
  int size=0;
  rLock.lock();
  while(loop&&running){
    rLock.unlock();
    if ((size = recv(sock, buffer, BUFFSIZE, 0)) > 0) {
      messageLock[me].lock();
      messages[me]= messages[me]+buffer;
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

std::string ChatServer::getMessages(int id){
  std::string getM;
  messageLock[id].lock();
  getM = messages[id];
  messages[id]="";
  messageLock[id].unlock();
  return getM;
}
bool ChatServer::sendMessage(int id, std::string message){
  return (send(clientSock[id], message.c_str(), message.length(), 0)!=message.length());
}
/*
Server Host that clients initially connect too.
*/
void ChatServer::serverLoop(){
  running = true;
  if ((serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) >= 0) {
    memset(&server, 0, sizeof(server));           // Clear struct 
    server.sin_family = AF_INET;                  // Internet/IP 
    server.sin_addr.s_addr = htonl(INADDR_ANY);   // Incoming addr 
    server.sin_port = htons(HOSTSOCK);            // server port 
    if (bind(serverSock, (struct sockaddr *) &server,sizeof(server) ) >= 0) {
      // Listen on the server socket
      if (listen(serverSock, MAXCONNECT) >= 0) {
	rLock.lock();
	while(running){
	  rLock.unlock();
	  unsigned int clientlen = sizeof(client);
	  if ((clientSockInit = accept(serverSock, (struct sockaddr *)&client,&clientlen)) >= 0){ // Grabing clinet info
	    inet_ntoa(client.sin_addr);
	    threadIds[current] = std::thread(&ChatServer::handleClient,this,clientSockInit, current);
	    clientSock[current] = clientSockInit;
	    current++; 
	  }
	  rLock.lock();
        }
	rLock.unlock();
      }
    }
  }
  close(serverSock);
  for(int lp1 =0; lp1!=current;lp1++){
    threadIds[lp1].join();
  }
}

void ChatServer::stopServer(){
  rLock.lock();
  running = false;
  rLock.unlock();
}

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
