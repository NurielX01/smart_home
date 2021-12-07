
TARGET= main

CXX= g++
CC=$(CXX)

CFLAGS= -g3 -pedantic

CXXFLAGS = -std=c++11
CXXFLAGS += -pedantic -Wall -Werror
CXXFLAGS += -g3 -pthread

CPPFLAGS = -I../inc
CPPFLAGS += -I../../inc
CPPFLAGS += -I../../inc/inl

SRC = ../../src
INC = ../../inc

check: $(TARGET)
	./$(TARGET)

main: main.cpp\
$(SRC)/incoder.cpp $(INC)/incoder.hpp\
$(SRC)/server_tcp.cpp $(INC)/server_tcp.hpp\
$(SRC)/agent_socket_container.cpp $(INC)/agent_socket_container.hpp\
$(SRC)/message_handler.cpp $(INC)/message_handler.hpp\
$(SRC)/server_socket.cpp $(INC)/server_socket.hpp\
$(SRC)/socket.cpp $(INC)/socket.hpp\
$(SRC)/selector.cpp $(INC)/selector.hpp\
$(SRC)/socket_container.cpp $(INC)/socket_container.hpp\
$(SRC)/agent.cpp $(INC)/agent.hpp\
$(SRC)/message_decoder.cpp $(INC)/message_decoder.hpp\
$(SRC)/smoke_detector_x01.cpp $(INC)/smoke_detector_x01.hpp\
$(SRC)/sprinkler_x01.cpp $(INC)/sprinkler_x01.hpp\
$(SRC)/subscribers.cpp $(INC)/subscribers.hpp\
$(SRC)/event_id.cpp $(INC)/event_id.hpp\
$(SRC)/event.cpp $(INC)/event.hpp\
$(SRC)/task_event_routing.cpp $(INC)/task_event_routing.hpp\
$(SRC)/server.cpp $(INC)/server.hpp\
$(SRC)/thread_pool.cpp $(INC)/thread_pool.hpp\
$(SRC)/semaphore.cpp $(INC)/semaphore.hpp\
$(SRC)/mutex.cpp $(INC)/mutex.hpp\
$(SRC)/sync_point.cpp $(INC)/sync_point.hpp\
$(SRC)/mutex_guard.cpp $(INC)/mutex_guard.hpp\
$(INC)/group_thread.hpp\
$(INC)/block_bounded_q.hpp\
$(INC)/callable.hpp\
$(INC)/thread.hpp\
$(INC)/atomic_value.hpp\



clean:
	$(RM) $(TARGET)

.PHONY: clean check
