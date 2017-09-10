# Decentralized Social Network Makefile!
CC = g++
CFLAGS = -g -std=c++11 -lpthread
DSN_LIB = DSNLib/chat.a DSNLib/chatServer.a

SYS := $(shell gcc -dumpmachine)
ifeq ($(OS),Windows_NT)
	# For windows...
	OS = windows...
else
	# For Linux!
	OS = linux
endif

DSN : dSN.cpp mainWindow.o
	${CC} ${CFLAGS} dSN.cpp connectWindow.o mainWindow.o -o DSN ${DSN_LIB} `pkg-config gtkmm-3.0 --cflags --libs` -L"wBin"
	@echo compiled on ${OS}

mainWindow.o: mainWindow.cpp mainWindow.h connectWindow.o
	${CC} ${CFLAGS} -c mainWindow.cpp `pkg-config gtkmm-3.0 --cflags --libs` -Wl,-static

connectWindow.o: connectWindow.cpp connectWindow.h
	${CC} ${CFLAGS} -c connectWindow.cpp `pkg-config gtkmm-3.0 --cflags --libs` -Wl,-static

clean:
	rm DSN *.o
