
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
$(INC)/mutex.hpp $(SRC)/mutex.cpp\
$(INC)/mutex_guard.hpp $(SRC)/mutex_guard.cpp\
$(INC)/semaphore.hpp $(SRC)/semaphore.cpp\
$(INC)/sync_point.hpp $(SRC)/sync_point.cpp\


clean:
	$(RM) $(TARGET)

.PHONY: clean check
