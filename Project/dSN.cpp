/*
Created By Laurie Harding-Russell
And ...(Please contribute!)

This is an application to allow the populas to control their own information.
Each and ever person will be a server and a client with out doing any work!

*/

// OS dependent includes

#ifdef _WIN32
#include <windows.h>

#elif __linux__
#include <stdio.h>
#include <thread>   // Seems more oop like then pthreads
#endif

// chat
#include "chatServer.h"
#include "chat.h"

// Graphics
#include <iostream>  // Until we make a gui

using namespace std;

int main(){
  ChatServer* host; // Start host right away.
  host = new ChatServer();
  thread hostThread(&ChatServer::serverLoop,host);
  Chat* clients[MAXCONNECT];
  thread clientThreads[MAXCONNECT];
  int current=0;
  // This will be replaced with an actual gui
  bool exit= true;
  int choice=0;
  string temp;
  string name;

  cout << "Resources Loaded!"<<endl;
  do{
    if(host->serverRunning()){
      cout << "**** Decentralized Social Network ****" <<endl;
    }else{
      cout << "**** Anti-social Network **** <-- Host not running."<<endl;
      cout << "Enter 7 and press enter. The Host thread might not"<<endl;
      cout << "be ready. If this persists the sock may be in use."<< endl;
      cout << "***************************************************"<<endl;
    }
    cout << "Your IP address is:" << ""<<" Local: " <<  "" <<endl;
    cout << "Enter the number beside the command you want"<<endl;
    cout << "1. Connect to other node (chat)" << endl; 
    cout << "2. New message?" <<endl;
    cout << "3. send message" <<endl;
    cout << "4. View others profile" <<endl;
    cout << "5. Connect to finder server"<< endl;
    cout << "6. exit" << endl;
    cin >> choice;
    switch(choice){
    case 1:
      cout << "What is their IP address?"<<endl;
      cin >>temp;
      cout << "What is their name?" << endl;
      cin >> name;
      clients[current] = new Chat(temp,name);
      if(clients[current]->getState()==20){ // Connect correctly?
	cout << "Connected!"<< endl;
	clientThreads[current] = thread(&Chat::messageCheckLoop,clients[current]);
	current++;
      }else{
	cout << "Failed to connect"<<endl;
	delete clients[current];
      }
      break;
    case 2:
    {
      int id=0;
      string who;
      cout << "Id number (will replace soon)"<<endl;
      cin >> id;
      cout << "Did you connect to them?" << endl;
      cin >> who;
      if (who=="yes"||who=="true"||who=="t"||who=="0"){
	cout << clients[id]->getMessage();
      }else{
	cout << host->getMessages(id);
      }
      cout << endl;
     }
    break;
    case 3:
    {
      int id;
      string who;
      string message;
      cout << "id number"<< endl;
      cin >> id;
      cout << "Did you connect to them?"<<endl;
      cin >> who;
      cout << "message?"<< endl;
      cin.ignore(1,'\n');
      getline (cin,message);
      if(who=="yes"||who=="true"||who=="t"||who=="0"){
	float check =clients[id]->sendMessage(message);
	cout << check*message.length() <<endl;
	if(check!=1){
	  cout << "Message sent ="<< check<<"%"<<endl;
	}
      }else{
	host->sendMessage(id,message);
      }
    }
    break;
    case 4:
      
      break;
    case 5:
      break;
    case 6:
      exit = false;
      break;
    default:
      cout << "Not an option" <<endl;
      break;
    }
  }while(exit);
  // ******************* Exit ***************************
  cout << "Release the magic imps"<<endl;
  host->stopServer(); // Need a way to stop accept connection...
  // hostThread.join();  // can't join until accept connection is cancelled.
  cout << "Released Mr. H" << endl;
  for(int lp1=0;lp1!=current;lp1++){
    cout << "Released" << lp1<< endl;
    clients[lp1]->endMessageCheckLoop(); // Stoping the loop
    //clientThreads[current].join();            // Waiting for thread
    //delete clients[lp1];  // causes system error
  }
  delete host;
  cout << "Dragons fed..." <<endl<<endl;
  return 0; // Should get Aborted since threads arn't joined.
}
