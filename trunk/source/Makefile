CC= gcc
EXEC= compilo
UNAME=`uname`

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

$(EXEC): y.tab.o lex.yy.o
	$(CC) -o $(EXEC) y.tab.o lex.yy.o -ll

clean: 
	rm -f compilateur y.output y.tab.h y.tab.c lex.yy.c *.o
