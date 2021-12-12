
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

INC = ../../inc

check: $(TARGET)
	./$(TARGET) -v

main: main.cpp\
$(SRC)/thread_pool.cpp\
$(SRC)/semaphore.cpp\
$(SRC)/mutex.cpp\
$(SRC)/sync_point.cpp\
$(SRC)/counter.cpp\
$(SRC)/mutex_guard.cpp\
../src/numbers.cpp\
../inc/numbers.hpp\
../src/thread_pool_helpers.cpp\
../inc/thread_pool_helpers.hpp\
$(INC)/counter.hpp\
$(INC)/group_thread.hpp\
$(INC)/thread_pool.hpp\
$(INC)/void_func_arg_adapter.hpp\
$(INC)/block_bounded_q.hpp\
$(INC)/atomic_value.hpp\
$(INC)/semaphore.hpp\
$(INC)/mutex.hpp\
$(INC)/callable.hpp\
$(INC)/thread.hpp\
$(INC)/sync_point.hpp\

clean:
	$(RM) $(TARGET)

.PHONY: clean check
