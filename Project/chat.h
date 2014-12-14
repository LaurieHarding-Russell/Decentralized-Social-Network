/* Holds all the data for Chat functions
*/

#ifndef chat_h
#define chat_h

#ifdef _WIN32
#include <windows.h>

#elif __linux__
 #include <stdio.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <arpa/inet.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <netinet/in.h>
 #include <mutex>
#endif

#include <string.h>

#define BUFFSIZE 128
#define HOSTSOCK 8000   // Hope that it isn't being used. Needs researching.

class Chat{
 public:
  Chat();// Unused.
  Chat(std::string address, std::string name);// Start a connection
  ~Chat();

  float sendMessage(std::string message);
  void messageCheckLoop(); // Checks for new messages
  int getState(); // 0= no connection,1= tried,20 = good, 30 = message failed
  void endMessageCheckLoop();
  std::string getMessage();

private:
  // Sock Stuff
   struct sockaddr_in client;
   std::string address;
   std::string name;
   bool ending;
   int sock;
   int failedState; // Keeps track of where it all went wrong...
   std::mutex rLock;
   // Message stuff
   std::mutex messageLock;
   std::string message;
};

#endif
