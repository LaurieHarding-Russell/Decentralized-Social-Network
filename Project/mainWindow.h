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
  //Signal handlers:
  void logIn();

  //Member widgets:
  Gtk::Box container; // Verticle array
  Gtk::Label userL;
  Gtk::Entry username;
  Gtk::Label passL;
  Gtk::Entry password;
  Gtk::Button logInB; // log in
};

#endif
