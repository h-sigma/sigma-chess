#makefile for chess GUI

.phony = clean

CXX = g++

CXXFLAGS = -W -Wall -Wno-return-type

LINKERFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

DEPENDS = GUIMain.o Board.o Utility.o

Main: ${DEPENDS}
	${CXX} -g -o gui ${CXXFLAGS} ${DEPENDS} ${LINKERFLAGS}

GUIMain.o : Board.hpp

Board.o : Board.hpp Types.hpp Utility.hpp

Utility.o : Utility.hpp

clean :
	-rm gui ${DEPENDS}
	-clear