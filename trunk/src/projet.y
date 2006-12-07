%{

#include <stdlib.h>
#include <stdio.h>
#include "y.tab.h"
#include "process.h" 

#define DEF_TRUE 1
#define DEF_FALSE 0

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

pv : PV 
     | ;

decl_list : decl_list decl
            | ;

decl : type id_aff_list PV { process_declaration(); } ;

id_aff_list : id_aff_list VIR id_aff { $$ = $1; }
              | id_aff { $$ = $1; };

id_aff : id { $$ = $1; }
         | affect { $$ = $1; };

id : ID { $$ = $1; };

type : INT {/* gestion de la remontee des types a faire */ }
       | FLOAT 
       | BOOL 
       | type STAR ;

inst_list : inst_list PV inst
            | inst ;

inst : affect
       | cond
       | loop
       | bloc ;

affect : id EQ exp { $$ = process_assignment($1,$3); };

cond : IF exp THEN inst 
       | IF exp THEN inst ELSE inst;

loop : while exp_do inst { process_while_end($1,$2); }
       | repeat inst UNTIL exp { process_repeat_end($1,$4); };

while: WHILE { $$ = process_while_begin(); };

exp_do: exp DO { $$ = process_exp_do_begin($1); };

repeat: REPEAT { $$ = process_repeat_begin(); };

bloc : da prog fa { $$=$2; };

da : DA { process_context_open(); };

fa : FA { process_context_save(); };

exp :  exp OR exp { process_or($1,$3); }
     | exp AND exp { process_and($1,$3); }
     | exp PLUS exp { process_plus($1,$3); }
     | exp MOINS exp { process_moins($1,$3); }
     | exp STAR exp { process_star($1,$3); }
     | exp DIV exp { process_div($1,$3); }
     | exp EQL exp { process_eql($1,$3); }
     | exp GRT exp { process_grt($1,$3); }
     | exp LOW exp { process_low($1,$3); }
     | exp NEQ exp { process_neq($1,$3); }
     | uop exp %prec MUNAIRE { process_uop($1,$2); }
     | DP exp FP { $$ = $2; }
     | id { $$ = $1; }
     | const { $$ = $1; }; 

const : NUM { $$ = $1; }
        | TRUE { $$ = DEF_TRUE; }
        | FALSE { $$ = DEF_FALSE; };

uop : STAR { /*remonter star*/ }
      | MOINS { /*idem moins*/ }
      | NOT {/*idem not*/ };

%%

int yyerror(char *s)
{ 
  return printf("%s\n",s);
}
   
int main()
{
  return yyparse();
}
