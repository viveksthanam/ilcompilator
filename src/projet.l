/* specifications des tokens */

%{

#include "y.tab.h"
#include "hashtable.h"
#include "lex_process.h"
#include "contextstack.h"

extern int yyval;
extern int yyval_int;
extern float yyval_float;
extern CHashtable* HT_main;
extern CContextStack* CS_main;
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
[a-zA-Z][a-zA-Z0-9]*         {  yyval = lex_process_getTinyStringID( HT_main, yytext ); 
			       										return(ID);}
[0-9]+(".")[0-9]*            { yyval_float = lex_process_atof(yytext); return(NUM_F);}
[0-9]			     							 { yyval_int = lex_process_atoi(yytext); return(NUM_I);}

