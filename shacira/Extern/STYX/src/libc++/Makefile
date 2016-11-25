CXXFLAGS=-Wall -O2 -g
LDFLAGS=-lstdc++

all: libstyxc++.a StyxScannerTest StyxParseTreeTest

StyxScannerTest: StyxScannerTest.o StyxUtil.o libstyxc++.a 

StyxParseTreeTest: StyxParseTreeTest.o StyxUtil.o libstyxc++.a 

libstyxc++.a: StyxScanner.o StyxI18NLit.o StyxString.o StyxGrammar.o StyxParseTable.o
	ar r $@ $^

clean:
	-rm *.o *.bak *.a StyxScannerTest StyxParseTreeTest

depend:
	makedepend -Y -- $(CXXFLAGS) -- *.[Cch] 2>/dev/null

# DO NOT DELETE

StyxGrammar.o: StyxGrammar.h
StyxI18NLit.o: StyxI18NLit.h
StyxParseTable.o: StyxParseTable.h StyxString.h StyxGrammar.h StyxParser.h
StyxParseTable.o: StyxString.h StyxGrammar.h StyxParser.h
StyxParseTree.o: StyxStreamParser.h StyxString.h StyxGrammar.h StyxScanner.h
StyxParseTree.o: StyxParseTable.h StyxParser.h StyxTree.h
StyxParseTreeTest.o: StyxParseTree.h StyxStreamParser.h StyxString.h
StyxParseTreeTest.o: StyxGrammar.h StyxScanner.h StyxParseTable.h
StyxParseTreeTest.o: StyxParser.h StyxTree.h StyxUtil.h
StyxScanner.o: StyxScanner.h StyxString.h
StyxScannerTest.o: StyxStreamParser.h StyxString.h StyxGrammar.h
StyxScannerTest.o: StyxScanner.h StyxParseTable.h StyxParser.h StyxUtil.h
StyxStreamParser.o: StyxString.h StyxGrammar.h StyxScanner.h StyxParseTable.h
StyxStreamParser.o: StyxParser.h
StyxString.o: StyxString.h
StyxUtil.o: StyxUtil.h
