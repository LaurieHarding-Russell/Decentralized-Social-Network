#include "mainWindow.h"

MainWindow::MainWindow()
  :conversation("connect"){
  set_border_width(5);
  conversation.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onConv));
  add(conversation);
  conversation.show();
}

void MainWindow::onConv(){
  
}
MainWindow::~MainWindow(){

}
