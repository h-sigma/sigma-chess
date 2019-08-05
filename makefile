#makefile for chess GUI

.phony = clean

CXX = g++

CXXFLAGS = -std=c++17 -W -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast 

LINKERFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -pthread

DEPENDS = GUIMain.o Application.o BoardAPI.o Board.o Utility.o Coin.o UCI.o

Main: ${DEPENDS}
	${CXX} -g -o gui  ${CXXFLAGS} ${DEPENDS} ${LINKERFLAGS}

GUIMain.o : Application.hpp

Application.o : BoardAPI.hpp UCI.o

BoardAPI.o : Board.hpp

Board.o : Types.hpp Utility.hpp ResourceHolder.hpp ResourceIdentifier.hpp Coin.hpp

Coin.o : Types.hpp Utility.hpp ResourceHolder.hpp ResourceIdentifier.hpp Board.hpp

Utility.o : ResourceIdentifier.hpp Types.hpp

UCI.o : UCI.hpp

clean :
	-rm gui ${DEPENDS}
	-clear