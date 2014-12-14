/*
Holds all the data for Chat server functions.
I will probably make this into a static class since I don't see 
a reason for haveing multiple instances of the host module.

*/

#ifndef chatServer_h
#define chatServer_h

#ifdef _WIN32
#include <windows.h>

#elif __linux__
 #include <stdio.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <netinet/in.h>
 #include <thread>
 #include <mutex>
#endif

#include <string.h>
#define BUFFSIZE 128
#define HOSTSOCK 8000   // Hope that it isn't being used. Needs researching.

// No one talks to more than a 100 people at once... right?
#define MAXCONNECT 100

class ChatServer{
public:
  ChatServer();
  void serverLoop();
  void stopServer();
  bool serverRunning(); // Is the server running?
  std::string getMessages(int id);// Will be replaceing this entirely.
  bool sendMessage(int id,std::string message);
  ~ChatServer();
private:
  std::mutex rLock; // Locks running. 
  bool running;     // Is the Host running?
  std::thread threadIds[MAXCONNECT];   // One thread per conversation
  void handleClient(int sock, int me); // threaded
  struct sockaddr_in server, client;
  int serverSock,clientSockInit;
  int clientSock[MAXCONNECT];
  std::string messages[MAXCONNECT];
  std::mutex messageLock[MAXCONNECT];
  int current;// Current connection number
};




#endif
