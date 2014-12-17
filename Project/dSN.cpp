/*
Created By Laurie Harding-Russell
And ...(Please contribute!)

This is an application to allow the populas to control their own information.
Each and ever person will be a server and a client with out doing any work!

*/

// OS dependent includes

#ifdef _WIN32

#elif __linux__

#endif

// Graphics
#include <iostream>  // Until we make a gui
#include <gtkmm/application.h>
#include "mainWindow.h"

using namespace std;

int main(int argc, char *argv[]){
  // ***************** graphic set up *****************************
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc,argv,"Decentralized.Social.Network");
  MainWindow mainW;
  
   /* 
    if(host->serverRunning()){
      cout << "**** Decentralized Social Network ****" <<endl;
    }else{
      cout << "**** Anti-social Network **** <-- Host not running."<<endl;
      cout << "Enter 7 and press enter. The Host thread might not"<<endl;
      cout << "be ready. If this persists the sock may be in use."<< endl;
      cout << "***************************************************"<<endl;
    }
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
      }*/
  return app->run(mainW); // Should get Aborted since threads arn't joined.
}
