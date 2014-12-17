#ifndef Main_Window_h
#define Main_Window_h

#include <gtkmm.h>
#include <gtkmm/window.h>

class MainWindow : public Gtk::Window
{

public:
  MainWindow();
  virtual ~MainWindow();

protected:
  //**** Signal handlers**** 
  void logIn();
  // Userpage
  void connectHandler();

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
   Gtk::Label userPhoto;
   Gtk::Box options;
   Gtk::Button connect,cellForward,finder,logout;
   Gtk::Label otherStuff;

 private:
  std::string myUsername;
  std::string myPassword;
};

#endif
