CXXFLAGS=-Wall -O2 -fno-rtti -g
LDFLAGS=-lstdc++

all: libstyxc++.a t

t: t.o libstyxc++.a 

libstyxc++.a: StyxScanner.o StyxI18NLit.o
	ar r $@ $^

clean:
	-rm *.o *.bak *.a

depend:
	makedepend -Y -- $(CXXFLAGS) -- *.[Cch] 2>/dev/null

# DO NOT DELETE
