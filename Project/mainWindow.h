#ifndef MainWindowh
#define MainWindowh

#include <list>
// chat
#include "chatServer.h"
#include "chat.h"
#include <thread>
#include <ctime>

// graphics
#include <gtkmm.h>
#include <gtkmm/window.h>
#include "connectWindow.h"

#include <iostream>	// For testing purposes only.

struct Post{
	std::string message;
	std::time_t stamp;
	Chat* owner;
};

class MainWindow : public Gtk::Window{

public:
	/*
	Constructor
	Purpose: Creates the Main window.
	Returns: NA
	*/
	MainWindow();
	/*
	Destructor
	Purpose: destroys the main window
	Returns: NA
	*/
	virtual ~MainWindow();

protected:
	//**** Signal handlers**** 
	/*
	logIn
	Purpose: It input from username and password and logs it in.
	Returns: NA
	*/
	void logIn();
	// Userpage
	/*
	connectH
	Purpose: Creates a new connectWindow.
	Returns: NA
	*/
	void connectH();
	/*
	logoutH
	Purpose: logout the user.
	Returns: NA
	*/
	void logoutH();
	//timer
	/*
	update
	Purpose: Checks for new connections.
	Returns: NA
	*/
	void update();
	int current=0;
	//Member widgets:
	Gtk::Notebook frame; // Switch pages
	Gtk::Box logInFrame; // Verticle array
	Gtk::Box userFrame;

	// ******** Login *********
	Gtk::Label userL;
	Gtk::Entry username;
	Gtk::Label passL;
	Gtk::Entry password;
	Gtk::Button logInB; // log in

	// ******* User Page **********
	std::string userPhotoName;
	Gtk::Label userName;	// 
	Gtk::Image userPhoto; // 
	Gtk::Box options;		 // 
	Gtk::Button connect,cellForward,finder,logout; // 
	Gtk::ScrolledWindow feedScroll;
	Gtk::Box feedFrame;
	Gtk::Label otherStuff; // 
	std::list<Post*> feedBuffer;
 private:
	ChatServer* host; // Start host right away.
	ConnectWindow chatBox;
	 
	std::list<ConnectWindow*> chatBoxes;
	Chat* clients[MAXCONNECT];
	 
	std::thread hostThread;
	std::thread clientThreads[MAXCONNECT];

	std::string myUsername;
	std::string myPassword;

	sigc::connection updateHandler;
	bool loggedIn;
};

#endif
