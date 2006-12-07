%{

#include <stdlib.h>
#include <stdio.h>
#include "y.tab.h"
#include "process.h"
#include "debug.h"

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

pv : PV { debug_echo("PV"); }
     | ;

decl_list : decl_list decl { debug_echo("decl_list decl"); }
            | ;

decl : type id_aff_list PV { process_declaration($1, $2); } ;

id_aff_list : id_aff_list VIR id_aff { $$ = $1; debug_echo("id_aff_list VIR id_aff"); }
              | id_aff { $$ = $1; debug_echo("id_aff"); };

id_aff : id { $$ = $1; debug_echo("id"); }
         | affect { $$ = $1; debug_echo("affect"); };

id : ID { $$ = $1; debug_echo("ID"); };

type : INT {/* gestion de la remontee des types a faire */ $$ = debug_echo("INT"); }
       | FLOAT { debug_echo("FLOAT"); } 
       | BOOL { debug_echo("BOOL"); }
       | type STAR { debug_echo("STAR"); };

inst_list : inst_list PV inst { debug_echo("inst_list PV inst"); }
            | inst { debug_echo("inst"); };

inst : affect { debug_echo("affect"); }
       | cond { debug_echo("cond"); }
       | loop { debug_echo("loop"); }
       | bloc { debug_echo("bloc"); };

affect : id EQ exp { $$ = process_assignment($1,$3); };

cond : IF exp THEN inst { debug_echo("IF exp THEN inst"); }
       | IF exp THEN inst ELSE inst { debug_echo("IF exp THEN inst ELSE inst"); };

loop : while exp_do inst { process_while_end($1,$2); }
       | repeat inst UNTIL exp { process_repeat_end($1,$4); };

while: WHILE { $$ = process_while_begin(); };

exp_do: exp DO { $$ = process_exp_do_begin($1); };

repeat: REPEAT { $$ = process_repeat_begin(); };

bloc : da prog fa { $$=$2; debug_echo("da prog fa"); };

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
     | DP exp FP { $$ = $2; debug_echo("DP exp FP"); }
     | id { $$ = $1; debug_echo("id"); }
     | const { $$ = $1; debug_echo("const"); }; 

const : NUM { $$ = $1; debug_echo("NUM"); }
        | TRUE { $$ = DEF_TRUE; debug_echo("TRUE"); }
        | FALSE { $$ = DEF_FALSE; debug_echo("FALSE"); };

uop : STAR { /*remonter star*/ debug_echo("STAR"); }
      | MOINS { /*idem moins*/ debug_echo("MOINS"); }
      | NOT {/*idem not*/ debug_echo("NOT"); };

%%

int yyerror(char *s)
{ 
  return printf("%s\n",s);
}
   
int main()
{
  debug_echo("appel yyparse");
  return yyparse();
  debug_echo("fin de yyparse");
}
