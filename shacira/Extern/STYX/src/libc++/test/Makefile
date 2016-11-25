CXXFLAGS=-Wall -O2 -g -I..
LDFLAGS=-lstdc++

all: StyxValueTest StyxTreeTest

StyxValueTest: StyxValueTest.o ../libstyxc++.a 

StyxTreeTest: StyxTreeTest.o ../libstyxc++.a 

clean:
	-rm *.o *.bak *.a StyxValueTest StyxTreeTest

depend:
	makedepend -Y -- $(CXXFLAGS) -- *.[Cch] 2>/dev/null

# DO NOT DELETE

StyxTreeTest.o: ../StyxTree.h
StyxValueTest.o: StyxValue.h
t.o: StyxValue.h
