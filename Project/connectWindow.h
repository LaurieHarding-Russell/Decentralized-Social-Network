#ifndef connectWindow_h
#define connectWindow_h

#include <gtkmm.h>
#include <gtkmm/window.h>
#include <thread>
#include "chat.h"

class ConnectWindow : public Gtk::Window{
public:
  ConnectWindow();
  virtual ~ConnectWindow();
protected:
  //Signal Handlers
  void connect();
  void sendMessage();
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
  //Glib::RefPtr<Gtk::TextBuffer> conversationB;
  Gtk::Entry messageE;
  Gtk::Button sendB;
  // ******* User Page ************
 private:
  Chat* client;
  std::thread clientThread;
  std::string name;
  std::string ip;
};
#endif
