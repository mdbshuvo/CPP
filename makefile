#This is a makefile for this project

all: Banking_management

Banking_management: main.o new.o view.o delete.o search.o update.o classFunc.o
	g++ main.o new.o view.o delete.o search.o update.o classFunc.o -o bankingManagement

main.o: main.cpp
	g++ -c main.cpp

new.o: new.cpp
	g++ -c new.cpp

view.o: view.cpp
	g++ -c view.cpp

delete.o: delete.cpp
	g++ -c delete.cpp

search.o: search.cpp
	g++ -c search.cpp

update.o: update.cpp
	g++ -c update.cpp

classFunc.o: classFunc.cpp
	g++ -c classFunc.cpp

clean:
	del *.o *.exe

rebuild: clean all
