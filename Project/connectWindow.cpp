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
	// user photo
	userPhotoName = "";
	// <-------  Load in photo name here 
  
	if(userPhotoName!=""){
	// userPhoto = Gtk::Image().get_pixbuf();
	}
	userPFrame.pack_start(userPhoto,Gtk::PACK_SHRINK);

	userName.set_label("Username");
	userPFrame.pack_start(userName);
 
	// New's Feed *Dynamically Generated*
	feedScroll.set_border_width(5);
	feedScroll.add(feedFrame);
	feedScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	userPFrame.pack_start(feedScroll);
  
	//********************************************/
	frame.append_page(connectFrame, "Connect");
	frame.append_page(talkFrame, "Message");
	frame.append_page(userPFrame, "Users page");
	show_all_children();
}

/***********************************************
               Host connected
************************************************/
ConnectWindow::ConnectWindow(Chat* c):
talkFrame(Gtk::ORIENTATION_VERTICAL),
userPFrame(Gtk::ORIENTATION_VERTICAL){
	set_default_size(300, 300); // size
	set_border_width(5);// border
	add(frame);
	// Message Box
	messageScroll.set_border_width(5);
	messageScroll.set_size_request(70,50);
	conversation.set_editable(false);
	conversation.get_buffer()->set_text("");
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
	frame.append_page(talkFrame, "Message");
	frame.append_page(userPFrame, "Users page");

	show_all_children();

	// Connection Part
	client=c;
	clientThread = std::thread(&Chat::messageCheckLoop,client);
	
	name = "bla";
	ip = "bla";

	sigc::slot<bool>mySlot = sigc::mem_fun(*this,&ConnectWindow::update);
	Glib::signal_timeout().connect(mySlot, 100); // 10x a second
}

// ***************** Signal Handlers *****************
void ConnectWindow::connect(){
	name = nameE.get_text();
	ip = ipAddressE.get_text();
	//if (client!=NULL){ // Delete client if new connection
	//  delete client;
	//}
	client = new Chat(ip);
	if(client->getState()==20){ // Connect correctly?
		std::cout << "Connected!"<< std::endl;
		clientThread = std::thread(&Chat::messageCheckLoop,client);
		sigc::slot<bool>mySlot = sigc::mem_fun(*this,&ConnectWindow::update);
		Glib::signal_timeout().connect(mySlot, 100); // 10x a second
		frame.set_current_page(1);
	}else{
		std::cout << "Failed to connect"<<std::endl;
		delete client;
	}
}

void ConnectWindow::sendMessage(){
	std::cout << client->getState() <<'\n';
	std::string getMessage = messageE.get_text()+'\n';
	messageE.set_text("");
	conversation.get_buffer()->insert_at_cursor(getMessage);
	int check=client->sendMessage(getMessage);
	std::cout << check<<'\n';
}
// *********** timer events *****************
bool ConnectWindow::update(){
	std::string incoming=client->getMessage();
	if(incoming[0] == '~'){
		if(incoming.compare("~/exit")==0){ // On exit. I could also do this at a higher level.
			client->endMessageCheckLoop();
			conversation.get_buffer()->insert_at_cursor("Disconnected!");
		}
		// userpage
	}else if(incoming!=""){
		conversation.get_buffer()->insert_at_cursor(incoming);
	}
	return true;
}

ConnectWindow::~ConnectWindow(){
	if (client!=NULL){
		client->endMessageCheckLoop(); // Stoping the loop
		clientThread.join();            // Waiting for thread
		delete client;
	}
}
