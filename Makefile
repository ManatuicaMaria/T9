cc = g++
CFLAGS = -Wall -Wextra -g -o
SRC = t9.cc
EXE = tema4

build:
	$(cc) $(CFLAGS) $(EXE) $(SRC)
clean:
	rm $(EXE)
run:
	./tema4
