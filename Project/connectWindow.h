#ifndef connectWindow_h
#define connectWindow_h

#include <gtkmm.h>
#include <gtkmm/window.h>
#include <thread>
#include "chat.h"
#include "chatServer.h"

class ConnectWindow : public Gtk::Window{
public:
  ConnectWindow();
  ConnectWindow(ChatServer* con,int current,std::string temp);
  virtual ~ConnectWindow();
protected:
  //Signal Handlers
  void connect();
  void sendMessage();
  void sendMessage2();
  bool update();
  bool update2();
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
 private:
  Chat* client;
  ChatServer* host;
  int id;
  std::thread clientThread;
  std::string name;
  std::string ip;
};
#endif
