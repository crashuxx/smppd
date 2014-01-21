
# Environment 
MKDIR=mkdir
CXX=g++
CC=gcc
CXXFLAGS=-Iinclude/
LFLAGS=

CXXFILES=src/main.cpp

# build
build: 
	$(CC) $(CXXFLAGS) $(LFLAGS) $(CXXFILES) -o bin/smppd

# clean
clean: 
	
	
all: 

# build tests
build-tests: 

# run tests
test: 

# help
help: 