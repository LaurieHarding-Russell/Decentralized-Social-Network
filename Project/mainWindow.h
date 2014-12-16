#ifndef Main_Window_h
#define Main_Window_h

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class MainWindow : public Gtk::Window
{

public:
  MainWindow();
  virtual ~MainWindow();

protected:
  //Signal handlers:
  void onConv();
  //Member widgets:
  Gtk::Button conversation;
};

#endif
