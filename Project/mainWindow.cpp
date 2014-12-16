#include "mainWindow.h"

MainWindow::MainWindow():
  container(Gtk::ORIENTATION_VERTICAL),
  logInB("log in"){

  // window stuff
  set_default_size(300, 350); // size
  set_border_width(5);// border
  add(container);

  // Username
  userL.set_label("User Name");
  container.pack_start(userL,Gtk::PACK_SHRINK);

  username.set_max_length(50); 
  username.select_region(0, 50);
  container.pack_start(username,Gtk::PACK_SHRINK);

  // Password
  passL.set_label("Password");
  container.pack_start(passL,Gtk::PACK_SHRINK);

  password.set_max_length(50);
  password.select_region(0, 50);
  container.pack_start(password, Gtk::PACK_SHRINK);


  // signals
  logInB.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::logIn));
  container.pack_start(logInB,Gtk::PACK_SHRINK);
  
  show_all_children();
 
}

void MainWindow::logIn(){
  
}
MainWindow::~MainWindow(){

}
