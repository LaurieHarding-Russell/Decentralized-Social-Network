#include "mainWindow.h"

MainWindow::MainWindow():
  logInFrame(Gtk::ORIENTATION_VERTICAL),
  userFrame(Gtk::ORIENTATION_VERTICAL),
  options(Gtk::ORIENTATION_HORIZONTAL),
  logInB("log in"){

  // window stuff
  set_default_size(300, 300); // size
  set_border_width(5);// border

  add(frame);
  frame.set_show_tabs(false);
  // ***************** Login Layout ****************************
  // Username
  userL.set_label("User Name");
  logInFrame.pack_start(userL,Gtk::PACK_SHRINK);

  username.set_max_length(50); 
  username.select_region(0, 50);
  logInFrame.pack_start(username,Gtk::PACK_SHRINK);

  // Password
  passL.set_label("Password");
  logInFrame.pack_start(passL,Gtk::PACK_SHRINK);

  password.set_max_length(50);
  password.select_region(0, 50);
  logInFrame.pack_start(password, Gtk::PACK_SHRINK);


  // signals
  logInB.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::logIn));
  logInFrame.pack_start(logInB,Gtk::PACK_SHRINK);

  // ********************** User's Page *********************
  // user photo
  userPhoto.set_label("Username");
  userFrame.pack_start(userL,Gtk::PACK_SHRINK);
  // User options
  connect.set_label("Connect");
  options.pack_start(connect,Gtk::PACK_SHRINK);
  
  cellForward.set_label("Cell Forwarding");
  options.pack_start(cellForward,Gtk::PACK_SHRINK);
  
  finder.set_label("Finder Service");
  options.pack_start(finder,Gtk::PACK_SHRINK);
  
  logout.set_label("logout");
  options.pack_start(logout);

  userFrame.pack_start(options,Gtk::PACK_SHRINK);

  // Other Stuff
  otherStuff.set_label("Other Stuff");
  userFrame.pack_start(otherStuff);

  // ************************************
  frame.append_page(logInFrame);
  frame.append_page(userFrame);
  show_all_children();
}

void MainWindow::logIn(){
  myUsername= username.get_buffer();
  myPassword= password.get_buffer();
  // Hashing stuff to go here
  set_title("User Page");
  frame.set_current_page(1);
}
MainWindow::~MainWindow(){

}
