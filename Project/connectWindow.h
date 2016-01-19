#ifndef connectWindow_h
#define connectWindow_h

#include <gtkmm.h>
#include <gtkmm/window.h>
#include <thread>
#include "chat.h"
#include "chatServer.h"
#include <string>

#include <iostream>	// For testing purposes only.

class ConnectWindow : public Gtk::Window{
public:
	/*
	Constructor
	Purpose: Create a ConnectWindow. 
	Returns: NA
	*/
	ConnectWindow();
	/*
	Constructor
	Purpose: Create a ConnectWindow with a connection useing a Chat object. 
	Returns: NA
	*/
	ConnectWindow(Chat* c);
	/*
	Destructor
	Purpose: Create a ConnectWindow with a connection useing a Chat object. 
	Returns: NA
	*/
	virtual ~ConnectWindow();
protected:
	//Signal Handlers
	/*
	update
	Purpose: Deals timer event. Checks for new message etc.
	Returns: NA
	*/
	void connect();
	/*
	sendMessage
	Purpose: Sends Text from conversation TextView through the Chat Object.
	Returns: NA
	*/
	void sendMessage();
	/*
	update
	Purpose: Deals timer event. Gets Messages and processes them.
	Returns: NA
	*/
	bool update();
	// Layout
	Gtk::Notebook frame; // Switch pages
	Gtk::Box connectFrame;
	Gtk::Box talkFrame;
	Gtk::Box userPFrame;
	// ********* connect ************
	Gtk::Label ipAddressL;
	Gtk::Entry ipAddressE;
	Gtk::Label nameL;
	Gtk::Entry nameE;
	Gtk::Button connectB; 
	// ********* message **********
	Gtk::ScrolledWindow messageScroll;
	Gtk::TextView conversation;
	Gtk::Entry messageE;
	Gtk::Button sendB;
	// ******* User Page ************ 
	std::string userPhotoName;
	Gtk::Label userName;	// 
	Gtk::Image userPhoto; // 
	Gtk::ScrolledWindow feedScroll;
	Gtk::Box feedFrame;
	Gtk::Label otherStuff; // 

 private:
	Chat* client;
	std::thread clientThread;
	std::string name;
	std::string ip;
	bool loggedOn;
};
#endif
