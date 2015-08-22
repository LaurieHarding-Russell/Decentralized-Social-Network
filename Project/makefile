# Decentralized Social Network Makefile!
CC = g++
CFLAGS = -g -std=c++11 -lpthread

SYS := $(shell gcc -dumpmachine)
ifneq (, $(findstring linux, $(SYS)))
	# For Linux specific compiling stuff
	
else ifneq(, $(findstring mingw, $(SYS)))
	# Do mingw (windows) specific compiling stuff
	
endif

DSN : dSN.cpp mainWindow.o
	${CC} ${CFLAGS} dSN.cpp chat.o chatServer.o connectWindow.o mainWindow.o -o DSN `pkg-config gtkmm-3.0 --cflags --libs`

mainWindow.o: mainWindow.cpp mainWindow.h connectWindow.o chatServer.o chat.o
	${CC} ${CFLAGS} -c mainWindow.cpp `pkg-config gtkmm-3.0 --cflags --libs`

connectWindow.o: connectWindow.cpp connectWindow.h
	${CC} ${CFLAGS} -c connectWindow.cpp `pkg-config gtkmm-3.0 --cflags --libs`

chat.o : chat.cpp chat.h
	${CC} ${CFLAGS} -c chat.cpp 

chatServer.o : chatServer.cpp chatServer.h
	${CC} ${CFLAGS} -c chatServer.cpp

clean: 
	rm DSN *.o
