# Connor Stephens (cms3my) Decision Trees

CXX=clang++ $(CXXFLAGS)
CXXFLAGS = -Wall -g
OFILES = DTMake.o ITree.o ReciNode.o

.SUFFIXES: .o .cpp

main:  $(OFILES) 
	$(CXX) $(OFILES)
