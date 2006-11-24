CC= gcc
EXEC= compilo
UNAME=`uname`
CFLAGS= -Wall 
LFLAGS= -Wall

ifeq ($(UNAME),Linux)
#LINUX : BISON / FLEX

YACC= bison
LEX= flex

else
#SUNOS : YACC / LEX

YACC= yacc
LEX= lex

endif

all:	y.tab.h lex.yy.c y.tab.c $(EXEC)

y.tab.h :	projet.y
	$(YACC) -d -v projet.y -o y.tab.c

lex.yy.c:	projet.l   
	$(LEX) projet.l

y.tab.c:	projet.y
	$(YACC) -v projet.y

y.tab.o: 	y.tab.c
	$(CC) -c y.tab.c

lex.yy.o:	lex.yy.c
	$(CC) -c lex.yy.c

%.o: %.c
	$(CC) $(CFLAGS)

$(EXEC): y.tab.o lex.yy.o
	$(CC) $(LFLAGS) y.tab.o lex.yy.o -ll -o $(EXEC) 

clean: 
	rm -f compilateur y.output y.tab.h y.tab.c lex.yy.c *.o

distclean: 
	rm -f y.output y.tab.h y.tab.c lex.yy.c *.o

