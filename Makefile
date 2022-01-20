# Makefile
# Emmett Stein
# Homework - Gerp
# Output: executable named gerp

# defines compiler
CXX=clang++
# define flags
CXXFLAGS=-std=c++11 -O2 
# the 'default rule' is hw04
default: hw04
	

hash.o: hash.cpp hash.h stripAndlower.h index_dir.h
	$(CXX) $(CXXFLAGS) -c hash.cpp

interface.o: interface.cpp hash.cpp index_dir.h hash.h stripAndlower.h
	$(CXX) $(CXXFLAGS) -c interface.cpp
	
hw04: interface.o hash.o 
	$(CXX) $(CXXFLAGS) interface.o hash.o -o gerp
	
	
clean:
	-@rm -rf *.o 2>/dev/null
	
	