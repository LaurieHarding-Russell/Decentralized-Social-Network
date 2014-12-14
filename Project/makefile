# Decentralized Social Network Makefile!
CC = g++
CFLAGS = -g -std=c++11 -lpthread


DSN : dSN.cpp chatServer.o chat.o
	${CC} ${CFLAGS} dSN.cpp chat.o chatServer.o -o DSN

chat.o : chat.cpp chat.h
	${CC} ${CFLAGS} -c chat.cpp 

chatServer.o : chatServer.cpp chatServer.h
	${CC} ${CFLAGS} -c chatServer.cpp 

clean: 
	rm DSN chat.o chatServer.o