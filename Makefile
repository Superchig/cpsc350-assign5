CPPFLAGS=-g -Wall
CXX=g++

all: assignment5.exe

assignment5.exe: main.cpp Student.o Person.o Faculty.o
	$(CXX) $(CPPFLAGS) $^ -o $@

clean:
	rm *.o
	[ -f assignment5.exe ] && rm assignment5.exe
