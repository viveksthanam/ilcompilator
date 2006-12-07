%{

#include <stdlib.h>
#include <stdio.h>
#include "y.tab.h"

int yyerror(char *s);

// Ajouté car ne compilait pas
// avec g++
int yylex(void);

%}



%token VIR PV DP FP ID NUM NOT 
%token AND OR  
%token PLUS MOINS 
%token DIV STAR
%token LOW GRT NEQ EQL 
%token EQ 
%token DA FA 
%token TRUE FALSE 
%token INT FLOAT BOOL 
%token IF THEN ELSE REPEAT DO WHILE UNTIL


%start prog

%left AND OR  
%left PLUS MOINS 
%left DIV STAR
%left LOW GRT NEQ EQL 

%nonassoc THEN
%nonassoc ELSE
%nonassoc MUNAIRE

%%

prog : decl_list inst_list pv ;

pv : PV | ;

decl_list : decl_list decl
| ;

decl : type id_aff_list PV;

id_aff_list : id_aff_list VIR id_aff
| id_aff ;

id_aff : id | affect ;

id : ID ;

type : INT | FLOAT | BOOL | type STAR ;

inst_list : inst_list PV inst
| inst ;

inst : affect
       | cond
       | loop
       | bloc ;

affect : id EQ exp ;

cond : IF exp THEN inst 
| IF exp THEN inst ELSE inst;

loop : WHILE exp DO inst
| REPEAT inst UNTIL exp ;

bloc : DA prog FA ;

exp :  exp OR exp
     | exp AND exp
     | exp PLUS exp
     | exp MOINS exp
     | exp STAR exp
     | exp DIV exp
     | exp EQL exp
     | exp GRT exp
     | exp LOW exp
     | exp NEQ exp
     | uop exp %prec MUNAIRE
     | DP exp FP
     | id
     | const ; 

const : NUM | TRUE | FALSE ;

uop : STAR | MOINS | NOT;



%%

int yyerror(char *s)
{ 
  return printf("%s\n",s);
}
   
int main()
{
  return yyparse();
}
