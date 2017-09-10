# Decentralized Social Network Makefile!
CC = g++
CFLAGS = -g -std=c++11 -lpthread -fPIC

SYS := $(shell gcc -dumpmachine)
ifeq ($(OS),Windows_NT)
	# For windows...
	OS = windows...
else
	# For Linux!
	OS = linux
endif

DSNApiLibrary : chat.o chatServer.o
	ar rvs chat.a chat.o
	ar rvs chatServer.a chatServer.o
	mkdir -p DSNLib
	mv chat.a ./DSNLib/chat.a
	cp chat.h ./DSNLib/chat.h
	mv chatServer.a ./DSNLib/chatServer.a
	cp chatServer.h ./DSNLib/chatServer.h

chat.o : chat.cpp chat.h
	${CC} ${CFLAGS} -c chat.cpp

chatServer.o : chatServer.cpp chatServer.h
	${CC} ${CFLAGS} -c chatServer.cpp

clean:
	rm *.o
	rm -rf DSNLib
