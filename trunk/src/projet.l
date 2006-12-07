/* specifications des tokens */

%{

#include "y.tab.h"
#include "hashtable.h"
#include "lex_process.h"
extern int yylval;
extern CHashtable HT_main;
extern int lex_process_getTinyStringID( char* string );
%}

%%

"{"                          {return(DA);}
"}"                          {return(FA);}
","                          {return(VIR);}
"="                          {return(EQ);}
";"                          {return(PV);}
"("                          {return(DP);}
")"                          {return(FP);}
"+"                          {return(PLUS);}
"-"                          {return(MOINS);}
"*"                          {return(STAR);}
"/"                          {return(DIV);}
"if"                         {return(IF);}
"while"                      {return(WHILE);}
"do"                         {return(DO);}
"repeat"                     {return(REPEAT);}
"until"                      {return(UNTIL);}
"then"                       {return(THEN);}
"else"                       {return(ELSE);}
"|"                          {return(OR);}
"&"                          {return(AND);}
"false"                      {return(FALSE);}
"true"                       {return(TRUE);}
"!"                          {return(NOT);}
"<"                          {return(LOW);}
">"                          {return(GRT);}
"=="                         {return(EQL);}
"!="                         {return(NEQ);}
"int"                        {return(INT);}
"float"                      {return(FLOAT);}
"bool"                       {return(BOOL);}
[a-zA-Z][a-zA-Z0-9]*         { /** \note Voir commentaires dans lex_process.h */ 
			       yylval = lex_process_getTinyStringID( yytext ); 
			       return(ID);}
[0-9]+("."?)[0-9]*           {/** \todo  Retour NUM à gerer */ return(NUM);}

