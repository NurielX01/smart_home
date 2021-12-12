
TARGET= main

CXX= g++
CC=$(CXX)

CFLAGS= -g3 -pedantic

CXXFLAGS = -std=c++17
CXXFLAGS += -pedantic -Wall
CXXFLAGS += -g3 -pthread

CPPFLAGS = -I../../inc
CPPFLAGS += -I../../src
CPPFLAGS += -I../../../inc
CPPFLAGS += -I../../../inc/inl

INC = ../../../inc
SRC = ../../../src
INCTEST = ../../inc
SRCTEST = ../../src

check: $(TARGET)
	./$(TARGET)

main: main.cpp\
$(SRCTEST)/counter.cpp $(INCTEST)/counter.hpp\
$(SRCTEST)/numbers.cpp $(INCTEST)/numbers.hpp\
$(SRC)/semaphore.cpp $(INC)/semaphore.hpp\
$(SRC)/sync_point.cpp $(INC)/sync_point.hpp\
$(SRC)/mutex_guard.cpp $(INC)/mutex_guard.hpp\
$(INC)/group_thread.hpp\
$(INC)/void_method_void_adapt.hpp\
$(INC)/thread.hpp\
$(INC)/callable.hpp\
$(INC)/result_func_arg_adapter.hpp\
$(INC)/void_func_void_adapter.hpp\
$(INC)/result_func_two_args_adapter.hpp\

clean:
	$(RM) $(TARGET)

.PHONY: clean check
