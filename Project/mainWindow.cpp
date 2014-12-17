#include "mainWindow.h"
#include <iostream> // Testing! Purposes...
MainWindow::MainWindow():
  logInFrame(Gtk::ORIENTATION_VERTICAL),
  userFrame(Gtk::ORIENTATION_VERTICAL),
  options(Gtk::ORIENTATION_HORIZONTAL),
  logInB("log in"){

  // **************** window stuff ******************************
  set_default_size(300, 300); // size
  set_border_width(5);// border

  add(frame);
  frame.set_show_tabs(false);
  // ***************** Login Layout ****************************
  //* Username
  userL.set_label("User Name");
  logInFrame.pack_start(userL,Gtk::PACK_SHRINK);

  username.set_max_length(50); 
  username.select_region(0, 50);
  logInFrame.pack_start(username,Gtk::PACK_SHRINK);

  //* Password
  passL.set_label("Password");
  logInFrame.pack_start(passL,Gtk::PACK_SHRINK);

  password.set_max_length(50);
  password.select_region(0, 50);
  logInFrame.pack_start(password, Gtk::PACK_SHRINK);


  //* signals
  logInB.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::logIn));
  logInFrame.pack_start(logInB,Gtk::PACK_SHRINK);

  //********************** User's Page *********************
  // user photo
  userPhoto.set_label("Username");
  userFrame.pack_start(userPhoto,Gtk::PACK_SHRINK);

  userName.set_label("Username");
  userFrame.pack_start(userName);
  //* User options
  connect.set_label("Connect");
  connect.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::connectH));//Handler
  options.pack_start(connect,Gtk::PACK_SHRINK);

  cellForward.set_label("Cell Forwarding");
  // insert handler
  options.pack_start(cellForward,Gtk::PACK_SHRINK);
  
  finder.set_label("Finder Service");
  // insert handler
  options.pack_start(finder,Gtk::PACK_SHRINK);
  
  logout.set_label("logout");
  logout.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::logoutH));// Handler
  options.pack_start(logout);

  userFrame.pack_start(options,Gtk::PACK_SHRINK);

  //* Other Stuff */
  otherStuff.set_label("Other Stuff");
  userFrame.pack_start(otherStuff);
  
  
  /************************************/
  frame.append_page(logInFrame);
  frame.append_page(userFrame);
  show_all_children();
}
// ******************** Handers ***************************
void MainWindow::logIn(){
  myUsername= username.get_buffer();
  myPassword= password.get_buffer();
  // Hashing stuff to go here

  //****************** Server stuff ******************************
  host = new ChatServer();
  hostThread= std::thread(&ChatServer::serverLoop,host);
  current=0;
  // Graphic stuff 
  set_title("User Page");
  frame.set_current_page(1);
}

void MainWindow::connectH(){
  
}

void MainWindow::logoutH(){ // Very Broken
  myUsername="";
  myPassword="";
  std::cout << "Release the magic imps\n";
  host->stopServer(); // Need a way to stop accept connection...
  // hostThread.join();  // can't join until accept connection is cancelled.
  std::cout << "Released Mr. H\n";
  for(int lp1=0;lp1!=current;lp1++){
    std::cout << "Released" << lp1<< std::endl;
    clients[lp1]->endMessageCheckLoop(); // Stoping the loop
    //clientThreads[current].join();            // Waiting for thread
    //delete clients[lp1];  // causes system error
  }
  delete host;
  std::cout << "Dragons fed..." <<std::endl<<std::endl;
  set_title("Anti-Social Network");
  frame.set_current_page(1);
}
MainWindow::~MainWindow(){
 // ******************* Exit ***************************
  logoutH();
}
