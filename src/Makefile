CFLAG = -g -c -std=c++14 -fmax-errors=1 -pthread -I/usr/include/pcap
INCLUDE = -I../ -I/usr/local/include -I/home/zeta/Programming/mylibrary/
CC = g++
OBJ = $(patsubst %.cc, ../obj/%.o, $(wildcard *.cc))
MAIN_OBJ = $(patsubst %.cpp, ../obj/%.x, $(wildcard *.cpp))

all : $(OBJ) $(MAIN_OBJ)

../obj/%.o : %.cc 
	$(CC) $(INCLUDE) $(CFLAG) $< -o $@

../obj/%.x : %.cpp
	$(CC) $(INCLUDE) $(CFLAG) $< -o $@ 
