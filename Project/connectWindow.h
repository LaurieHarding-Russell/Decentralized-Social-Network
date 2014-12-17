#ifndef connectWindow_h
#define connectWindow_h

#include <gtkmm.h>
#include <gtkmm/window.h>

class ConnectWindow : public Gtk::Window{
public:
  ConnectWindow();
  virtual ~ConnectWindow();
protected:
  //Signal Handlers
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
  Glib::RefPtr<Gtk::TextBuffer> conversation;
  Gtk::Entry messageE;
  Gtk::Button sendB;
  // ******* User Page ************
  
 private:

};
#endif
