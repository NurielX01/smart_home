
TARGET= main

CXX= g++
CC=$(CXX)

CFLAGS= -g3 -pedantic

CXXFLAGS = -std=c++17
CXXFLAGS += -pedantic -Wall
CXXFLAGS += -g3 -pthread

CPPFLAGS = -I../../inc
CPPFLAGS += -I../../../inc
CPPFLAGS += -I../../../inc/inl

SRCTEST = ../../src
SRC = ../../../src
INC = ../../../inc

check: $(TARGET)
	./$(TARGET)

main: main.cpp\
$(INC)/thread.hpp\
$(INC)/group_thread.hpp\
$(INC)/block_bounded_q.hpp\
$(INC)/void_method_void_adapt.hpp\
$(INC)/callable.hpp\
$(SRC)/sync_point.cpp $(INC)/sync_point.hpp\
$(SRC)/mutex_guard.cpp $(INC)/mutex_guard.hpp\
$(SRC)/mutex.cpp $(INC)/mutex.hpp\
$(SRC)/semaphore.cpp $(INC)/semaphore.hpp\
$(SRCTEST)/producer.cpp\
$(SRCTEST)/consumer.cpp\


clean:
	$(RM) $(TARGET)

.PHONY: clean check
