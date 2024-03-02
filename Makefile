# Makefile
# Author: M00835210
# Created: 06/04/2023
# Updated: 18/04/2023

# Using g++ compiler
CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic
# TESTFLAGS = -Wa, -mbig-obj


.PHONY : all clean
all : tester program

tester : tracks_test.cpp maintracks.o tracks.o hashTable.o 
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiling program files
program : main.cpp maintracks.o tracks.o hashTable.o
# Instruction to build executables
	$(CXX) $(CXXFLAGS) -o $@ $^


# Building object main tracks
maintracks.o : maintracks.cpp maintracks.h 
	$(CXX) $(CXXFLAGS) -c $<

# Building object tracks
tracks.o : tracks.cpp tracks.h 
	$(CXX) $(CXXFLAGS) -c $<

# Building object tracks
hashTable.o : hashTable.cpp hashTable.h 
	$(CXX) $(CXXFLAGS) -c $<

clean :
	rm *.o
	rm *.exe