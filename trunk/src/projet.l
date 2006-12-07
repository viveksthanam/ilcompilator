/* specifications des tokens */

%{

#include "y.tab.h"
extern int yylval;

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
[a-zA-Z][a-zA-Z0-9]*         {/* a gerer */ yylval=0; return(ID);}
[0-9]+("."?)[0-9]*           {/* a gerer */ return(NUM);}
