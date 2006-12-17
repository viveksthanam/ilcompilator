%{

#include "hashtable.h"
#include "lex_process.h"
#include "contextstack.h"
#include "y.tab.h"

/** \addtogroup LexInitInstructions
* Fonctions, variables et commandes paramétrant Lex.
* @{
*/

/** \brief Afin que Lex termine proprement en vidant ses buffers, sans fuite
* mémoire, nous redéfinissons yyterminate().
*/
#define yyterminate() yy_delete_buffer(YY_CURRENT_BUFFER); return YY_NULL 

/** \brief Nous n'avons pas besoin de la fonction unput, cela évite une erreur en
* compilation -Wall du compilateur.
*/
#define YY_NO_UNPUT

extern int yyval_int;
extern float yyval_float;
extern CHashtable* HT_main;
extern CContextStack* CS_main;

/** \brief Dépile la pile des buffers de Lex, détruit chaque élément. Détruit 
* ensuite la pile.
*/
/*
int yylex_destroy (void)
{
	
	while (YY_CURRENT_BUFFER){
		yy_delete_buffer (YY_CURRENT_BUFFER );
		YY_CURRENT_BUFFER_LVALUE = NULL;
		yypop_buffer_state();
	}
	
	yyfree(yy_buffer_stack);
	yy_buffer_stack=NULL;
	yyfree(yy_start_stack);
	yy_start_stack=NULL;
	
	return(0);

}*/

/** @} */

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
[a-zA-Z][a-zA-Z0-9]*         { yylval = lex_process_getTinyStringID( HT_main, yytext ); 
			       									 return(ID);}
[0-9]+(".")[0-9]*            { yyval_float = lex_process_atof(yytext); return(NUM_F);}
[0-9]*			     						 { yyval_int = lex_process_atoi(yytext); return(NUM_I);}
"/*"[^}\n]*"*/"							 { /*mange les commentaires 'à la C'*/ }
[ \t\n]+										 { /*mange les espaces*/ }
