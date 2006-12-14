# vim: noexpandtab

CC= g++
EXEC= compilo
ALLEXEC= hashtable_test contextstack_test codewriter_test
CFLAGS= -Wall -g
LDFLAGS= -Wall -ll -g

LEX=flex
YACC=bison

OBJECTS = y.tab.o lex.yy.o lex_process.o process.o $(OBJECTS_WITHOUT_LY)

OBJECTS_WITHOUT_LY = hashtable.o debug.o contextstack.o declarationqueue.o instructionqueue.o instruction.o codewriter.o label.o

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXEC)

contextstack_test: $(OBJECTS_WITHOUT_LY) contextstack_test.cpp
	$(CC) -g contextstack_test.cpp $(OBJECTS_WITHOUT_LY) -o contextstack_test

hashtable_test: $(OBJECTS_WITHOUT_LY) hashtable_test.cpp
	$(CC) -g hashtable_test.cpp $(OBJECTS_WITHOUT_LY) -o hashtable_test

codewriter_test: $(OBJECTS_WITHOUT_LY) codewriter_test.cpp
	$(CC) -g codewriter_test.cpp $(OBJECTS_WITHOUT_LY) -o codewriter_test

%.o: %.cpp *.h
	$(CC) $(CFLAGS) $< -c -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@

y.tab.h: projet.y
	$(YACC) -d -v projet.y -o y.tab.c

y.tab.c: projet.y y.tab.h
	$(YACC) -v projet.y

lex.yy.c: projet.l
	$(LEX) projet.l

y.tab.o: y.tab.c
	$(CC) -c y.tab.c

lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c

clean: 
	rm -f $(EXEC) $(ALLEXEC) y.output y.tab.h y.tab.c lex.yy.c *.o

distclean: 
	rm -f y.output y.tab.h y.tab.c lex.yy.c *.o

