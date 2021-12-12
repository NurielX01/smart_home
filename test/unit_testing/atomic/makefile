
TARGET= main

CXX= g++
CC=$(CXX)

CFLAGS= -g3 -pedantic

CXXFLAGS = -std=c++11
CXXFLAGS += -pedantic -Wall
CXXFLAGS += -g3 -pthread

CPPFLAGS = -I../../inc
CPPFLAGS += -I../../../inc
CPPFLAGS += -I../../../inc/inl

SRC = ../../../src
INC = ../../../inc

check: $(TARGET)
	./$(TARGET)

main: main.cpp\
$(INC)/atomic_value.hpp

clean:
	$(RM) $(TARGET)

.PHONY: clean check
