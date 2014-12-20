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
  return app->run(mainW); // Should get Aborted since threads arn't joined.
}
