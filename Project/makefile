# Decentralized Social Network Makefile!
CC = g++
CFLAGS = -g -std=c++11 -lpthread

DSN : dSN.cpp chatServer.o chat.o mainWindow.o
	${CC} ${CFLAGS} dSN.cpp chat.o chatServer.o mainWindow.o -o DSN `pkg-config gtkmm-3.0 --cflags --libs`

mainWindow.o: mainWindow.cpp mainWindow.h connectWindow.o
	${CC} ${CFLAGS} -c mainWindow.cpp connectWindow.o `pkg-config gtkmm-3.0 --cflags --libs`

connectWindow.o: connectWindow.cpp connectWindow.h
	${CC} ${CFLAGS} -c connectWindow.cpp `pkg-config gtkmm-3.0 --cflags --libs`

chat.o : chat.cpp chat.h
	${CC} ${CFLAGS} -c chat.cpp 

chatServer.o : chatServer.cpp chatServer.h
	${CC} ${CFLAGS} -c chatServer.cpp 

clean: 
	rm DSN chat.o chatServer.o
