CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall
EXEC = main

$(EXEC): main.cpp matrix.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o main $<

clean:
	$(RM) *.o