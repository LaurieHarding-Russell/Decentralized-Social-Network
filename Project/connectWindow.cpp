#include "connectWindow.h"
#include <iostream>

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
  connectB.signal_clicked().connect(sigc::mem_fun(*this,&ConnectWindow::connect));

  connectFrame.pack_start(connectB,Gtk::PACK_SHRINK);

  //********* messenger Layout *****************
  // Message Box
  messageScroll.set_border_width(5);
  messageScroll.set_size_request(70,50);
  conversation.set_editable(false);
  messageScroll.add(conversation);
  messageScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  talkFrame.pack_start(messageScroll,Gtk::PACK_SHRINK);
  // Message input
  messageE.set_max_length(50);
  messageE.select_region(10,60);
  talkFrame.pack_start(messageE,Gtk::PACK_SHRINK);
  // Send
  sendB.set_label("Send");
  sendB.signal_clicked().connect(sigc::mem_fun(*this,&ConnectWindow::sendMessage));
  talkFrame.pack_start(sendB,Gtk::PACK_SHRINK);
  //********* User Page Layout *****************
  
  //********************************************/
  frame.append_page(connectFrame, "Connect");
  frame.append_page(talkFrame, "Message");
  frame.append_page(userPFrame, "Users page");
  show_all_children();
}
// ***********************************************
// *************** Host connected ****************
ConnectWindow::ConnectWindow(ChatServer* h, int num):
talkFrame(Gtk::ORIENTATION_VERTICAL),
userPFrame(Gtk::ORIENTATION_VERTICAL){
  // Message Box
  messageScroll.set_border_width(5);
  messageScroll.set_size_request(70,50);
  conversation.set_editable(false);
  messageScroll.add(conversation);
  messageScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  talkFrame.pack_start(messageScroll,Gtk::PACK_SHRINK);
  // Message input
  messageE.set_max_length(50);
  messageE.select_region(10,60);
  talkFrame.pack_start(messageE,Gtk::PACK_SHRINK);
  // Send
  sendB.set_label("Send");
  //sendB.signal_clicked().connect(sigc::mem_fun(*this,&ConnectWindow::sendMessage));
  frame.append_page(talkFrame, "Message");
  frame.append_page(userPFrame, "Users page");
  show_all_children();
  // Connection Part
  host=h;
  id = num;
  sigc::slot<bool>my_slot = sigc::mem_fun(*this,&ConnectWindow::update2);
  Glib::signal_timeout().connect(my_slot, 100); // 10x a second
}
// ***************** Signal Handlers *****************
void ConnectWindow::connect(){
  name = nameE.get_text();
  ip = ipAddressE.get_text();
  client = new Chat(ip,name);
  if(client->getState()==20){ // Connect correctly?
    std::cout << "Connected!"<< std::endl;
    clientThread = std::thread(&Chat::messageCheckLoop,client);
    sigc::slot<bool>my_slot = sigc::mem_fun(*this,&ConnectWindow::update);
    Glib::signal_timeout().connect(my_slot, 100); // 10x a second
  }else{
    std::cout << "Failed to connect"<<std::endl;
    delete client;
  }
}

void ConnectWindow::sendMessage(){
  std::string getMessage = messageE.get_text();
  messageE.set_text("");
  //conversation.insert_text(getMessage);
  float check=client->sendMessage(getMessage);
  if(check!=1){
    std::cout << "Message sent ="<< check<<"%"<<std::endl;
  }
}
// *********** timer events *****************
bool ConnectWindow::update(){
  std::string incoming=client->getMessage();
  if(incoming!=""){
    std::cout <<incoming;
  }
  return true;
}
bool ConnectWindow::update2(){
  std::string incoming= host->getMessages(id);
  if(incoming!=""){
    std::cout <<incoming;
  }
  return true;
}
// ****************************************************
ConnectWindow::~ConnectWindow(){
  std::cout << "Released" << std::endl;
  client->endMessageCheckLoop(); // Stoping the loop
  clientThread.join();            // Waiting for thread
  delete client;  // causes system error
}
