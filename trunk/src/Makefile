# vim: noexpandtab

CC= g++
EXEC= compilo
ALLEXEC= hashtable_test contextstack_test
UNAME=`uname`
CFLAGS= -Wall -g
LDFLAGS= -Wall -ll -g
OBJECTS = y.tab.o lex.yy.o hashtable.o lex_process.o process.o debug.o contextstack.o declarationqueue.o instructionqueue.o instruction.o codewriter.o

ifeq ($(UNAME),Linux)
#LINUX : BISON / FLEX

	YACC= bison
	LEX= flex

else
#SUNOS : YACC / LEX

	YACC= yacc
	LEX= lex

endif

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXEC)

contextstack_test: contextstack.o
	$(CC) -g contextstack.o contextstack_test.cpp -o contextstack_test

hashtable_test: hashtable.o
	$(CC) -g hashtable_test.cpp -o hashtable_test

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

