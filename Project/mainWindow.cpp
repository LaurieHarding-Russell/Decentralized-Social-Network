#include "mainWindow.h"
#include <iostream> 

MainWindow::MainWindow():
	logInFrame(Gtk::ORIENTATION_VERTICAL),
	userFrame(Gtk::ORIENTATION_VERTICAL),
	options(Gtk::ORIENTATION_HORIZONTAL),
	feedFrame(Gtk::ORIENTATION_VERTICAL),
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
	userPhotoName = "";
	// <-------	Load in photo name here 
	
	if(userPhotoName!=""){
		// userPhoto = Gtk::Image().get_pixbuf();
	}
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
	// New's Feed *Dynamically Generated*
	feedScroll.set_border_width(5);
	feedScroll.add(feedFrame);
	feedScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	userFrame.pack_start(feedScroll);
	
	
	/************************************/
	frame.append_page(logInFrame);
	frame.append_page(userFrame);
	show_all_children();
	loggedIn=false;
}
// ******************** Handers ***************************
void MainWindow::logIn(){
	myUsername= username.get_text();
	myPassword= password.get_text();
	// Hashing stuff to go here

	//****************** Server stuff ******************************
	host = new ChatServer();
	hostThread= std::thread(&ChatServer::serverLoop,host);
	// Graphic stuff 
	set_title("User Page");
	userName.set_label(myUsername);
	frame.set_current_page(1);
	// host timer
	sigc::slot<bool> mySlot = sigc::mem_fun(*this,&MainWindow::update);
	updateHandler= Glib::signal_timeout().connect(mySlot, 100); // 10x a second
	loggedIn=true;
}

void MainWindow::connectH(){
	ConnectWindow *newBox = new ConnectWindow();
	newBox->show();
	chatBoxes.push_back(newBox);
}

/* 
	 - Checks for new connections
	 - Checks for
*/
bool MainWindow::update(){
	std::string temp=host->getMessages(current);
	// Check for new connections!
	if(temp!=""){
		ConnectWindow *newBox = new ConnectWindow(host,current,temp);
		newBox->show();
		chatBoxes.push_back(newBox);
		current++;
	}
	// Check for new feed stuff!
	if(feedBuffer.empty()){
		//	chatBoxes;
	}

	return true;
}
/*
	Logs out, disconnects host. Should del
*/
void MainWindow::logoutH(){ // Very Broken
	//chatBoxes.clear();
	myUsername="";
	myPassword="";
	std::cout << "Release the magic imps\n";
	host->stopServer(); // Need a way to stop accept connection...
	hostThread.join();	// can't join until accept connection is cancelled.
	std::cout << "Released Mr. H\n";
	// detach update timer
	updateHandler.disconnect();
	delete host;			// Will find a work arround but... a good OS will grab back the memory.
	std::cout << "Dragons fed..." <<std::endl<<std::endl;
	set_title("Anti-Social Network");
	frame.set_current_page(0);
	loggedIn=false;
}
// ******************* Exit ***************************
MainWindow::~MainWindow(){
	if(loggedIn){
		logoutH();
	}
}
