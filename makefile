#makefile for chess GUI

.phony = clean

CXX = g++

CXXFLAGS = -W -Wall -Wno-return-type

LINKERFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

DEPENDS = GUIMain.o Application.o Board.o Utility.o Coin.o

Main: ${DEPENDS}
	${CXX} -g -o gui ${CXXFLAGS} ${DEPENDS} ${LINKERFLAGS}

GUIMain.o : Application.hpp

Application.o : Board.hpp

Board.o : Types.hpp Utility.hpp ResourceHolder.hpp ResourceIdentifier.hpp 

Coin.o : Types.hpp Utility.hpp ResourceHolder.hpp ResourceIdentifier.hpp

Utility.o : ResourceIdentifier.hpp Types.hpp

clean :
	-rm gui ${DEPENDS}
	-clear