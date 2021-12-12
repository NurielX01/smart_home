
TARGET= main

CXX= g++
CC=$(CXX)

CFLAGS= -g3 -pedantic

CXXFLAGS = -std=c++17
CXXFLAGS += -pedantic -Wall #-Werror
CXXFLAGS += -g3 -pthread

CPPFLAGS = -I../inc
CPPFLAGS += -I../../inc
CPPFLAGS += -I../../inc/inl

SRC = ../../src

check: $(TARGET)
	./$(TARGET)

main: main.cpp $(SRC)/counter.cpp $(SRC)/semaphore.cpp $(SRC)/sync_point.cpp\
../../inc/sync_point.hpp ../../inc/void_method_void_adapt.hpp ../../inc/counter.hpp ../src/numbers.cpp\
../../inc/thread.hpp ../../inc/callable.hpp ../../inc/result_func_arg_adapter.hpp\
../../inc/void_func_void_adapter.hpp ../../inc/result_func_two_args_adapter.hpp\
../../inc/void_method_void_adapt.hpp ../../inc/result_method_arg_adapt.hpp\
../../inc/result_method_two_args_adapt.hpp

clean:
	$(RM) $(TARGET)

.PHONY: clean check
