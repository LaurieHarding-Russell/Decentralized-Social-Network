#include "connectWindow.h"

ConnectWindow::ConnectWindow():
  connectFrame(Gtk::ORIENTATION_VERTICAL),
  talkFrame(Gtk::ORIENTATION_VERTICAL),
  userPFrame(Gtk::ORIENTATION_VERTICAL){

  //*********** window stuff ********************
  set_default_size(300, 300); // size
  set_border_width(5);// border
  add(frame);
  //********* connect layout *******************
  // Ip address
  ipAddressL.set_label("Ip Address");
  connectFrame.pack_start(ipAddressL,Gtk::PACK_SHRINK);

  ipAddressE.set_max_length(26);
  ipAddressE.select_region(0,50);
  connectFrame.pack_start(ipAddressE,Gtk::PACK_SHRINK);
  
  // Name
  nameL.set_label("name");
  connectFrame.pack_start(nameL,Gtk::PACK_SHRINK);

  nameE.set_max_length(26);
  nameE.select_region(0,50);
  connectFrame.pack_start(nameE,Gtk::PACK_SHRINK);
  // connect
  connectB.set_label("Connect");
  connectFrame.pack_start(connectB,Gtk::PACK_SHRINK);

  //********* messenger Layout *****************
  // Message Box
  
  // Message input
  messageE.set_max_length(50);
  messageE.select_region(0,60);
  talkFrame.pack_start(messageE,Gtk::PACK_SHRINK);
  // Send
  sendB.set_label("Send");
  talkFrame.pack_start(sendB,Gtk::PACK_SHRINK);
  //********* User Page Layout *****************
  
  //********************************************/
  frame.append_page(connectFrame, "Connect");
  frame.append_page(talkFrame, "Message");
  frame.append_page(userPFrame, "Users page");
  show_all_children();
}
ConnectWindow::~ConnectWindow(){
  
}
