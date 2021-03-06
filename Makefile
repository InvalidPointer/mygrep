CC = g++
CFLAGS = -g -O2 -std=c++11
BIN = ./bin/
.PHONY: all clean mygrep tester

all: $(BIN)/mygrep $(BIN)/tester

mygrep: $(BIN)/mygrep

tester: $(BIN)/tester

$(BIN)/tester: $(BIN)/tester.o $(BIN)/Regexp.o $(BIN)/RegexpChecker.o $(BIN)/SyntaxAnalyzer.o $(BIN)/LexicalAnalyzer.o
		$(CC) -o $(BIN)/tester $(BIN)/tester.o $(BIN)/Regexp.o $(BIN)/RegexpChecker.o $(BIN)/SyntaxAnalyzer.o $(BIN)/LexicalAnalyzer.o

$(BIN)/tester.o: tester.cpp Regexp.h | $(BIN)
		$(CC) $(CFLAGS) -c -o $(BIN)/tester.o tester.cpp

$(BIN)/mygrep: $(BIN)/mygrep.o $(BIN)/Regexp.o $(BIN)/RegexpChecker.o $(BIN)/SyntaxAnalyzer.o $(BIN)/LexicalAnalyzer.o
		$(CC) -o $(BIN)/mygrep $(BIN)/mygrep.o $(BIN)/Regexp.o $(BIN)/RegexpChecker.o $(BIN)/SyntaxAnalyzer.o $(BIN)/LexicalAnalyzer.o

$(BIN)/mygrep.o: main.cpp Regexp.h | $(BIN)
		$(CC) $(CFLAGS) -c -o $(BIN)/mygrep.o main.cpp

$(BIN)/Regexp.o: Regexp.cpp Regexp.h RegexpChecker.h SyntaxAnalyzer.h LexicalAnalyzer.h | $(BIN)
		$(CC) $(CFLAGS) -c -o $(BIN)/Regexp.o Regexp.cpp
        
$(BIN)/RegexpChecker.o: RegexpChecker.cpp RegexpChecker.h token.h rc_result.h | $(BIN)
		$(CC) $(CFLAGS) -c -o $(BIN)/RegexpChecker.o RegexpChecker.cpp

$(BIN)/SyntaxAnalyzer.o: SyntaxAnalyzer.cpp SyntaxAnalyzer.h token.h | $(BIN)
		$(CC) $(CFLAGS) -c -o $(BIN)/SyntaxAnalyzer.o SyntaxAnalyzer.cpp

$(BIN)/LexicalAnalyzer.o: LexicalAnalyzer.cpp LexicalAnalyzer.h token.h | $(BIN)
		$(CC) $(CFLAGS) -c -o $(BIN)/LexicalAnalyzer.o LexicalAnalyzer.cpp

$(BIN):
		mkdir -p $(BIN)

clean:
		-@rm -r $(BIN) 2>/dev/null || true
