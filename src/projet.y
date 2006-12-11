//% vim: tw=80 ts=2

%{

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "y.tab.h"
#include "configuration.h"
#include "process.h"
#include "debug.h"
#include "type.h"
#include "hashtable.h"
#include "contextstack.h"

// Ajouté car ne compilait pas
// avec g++
int yylex (void);
int yyval=0;
int yyval_int=0;
float yyval_float=0.0;

using namespace std;

/** \note Initialisation a NULL permettant d'effectuer des tests et de compiler
 * sans erreur, allocation dynamique au debut de main().
*/
CHashtable* HT_main = NULL;

/** \note Idem HT_main.
*/
CContextStack* CS_main = NULL;

/** \brief Variable globale conservant le type des ou de la derniere variable a
 * declarer, -1 voulant dire qu'il n'y a plus de variables a declarer pour
 * l'instruction courante.
*/ 
int current_decl_type = -1; 

/** \brief Etat du debug: 0 (défaut), ou 1 pour activer. Deux niveaux par
 * défaut, on pourra étendre par la suite.
*/
extern int debug_level;

/** \brief Sauve les meubles et quitte, si possible.
 */
void sanitizer (void) {

delete CS_main;
delete HT_main;

}

%}
 
%verbose

%token VIR PV DP FP ID NUM_I NUM_F NOT 
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

decl : type id_aff_list PV { process_declaration_end(); } ;

id_aff_list : id_aff_list VIR id_aff { process_declaration(current_decl_type,$3); }
              | id_aff { process_declaration(current_decl_type, $1); };

id_aff : id { $$ = $1; debug_echo("id"); }
         | affect { $$ = $1; debug_echo("affect"); };

id : ID { $$ = yylval; debug_echo("ID"); };

type : INT { $$ = T_INT; current_decl_type = T_INT; debug_echo("INT"); }
       | FLOAT { $$ = T_FLOAT; current_decl_type = T_FLOAT; debug_echo("FLOAT"); } 
       | BOOL { $$ = T_BOOL; current_decl_type = T_BOOL; debug_echo("BOOL"); }
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

const : NUM_I { $$ = $1; debug_echo("NUM_I"); }
        | NUM_F { $$ = $1; debug_echo("NUM_F"); }
        | TRUE { $$ = DEF_TRUE; debug_echo("TRUE"); }
        | FALSE { $$ = DEF_FALSE; debug_echo("FALSE"); };

uop : STAR { $$ = $1; debug_echo("STAR"); }
      | MOINS { $$ = $1; debug_echo("MOINS"); }
      | NOT { $$ = $1; debug_echo("NOT"); };

%%
  
int main( int argc, char** argv )
{
	
  about(); 
	debug_set_level( &argc, argv );

  debug_echo("creation HT principale");
	HT_main = new CHashtable;

 	debug_echo("création CS principale");
	CS_main = new CContextStack;

	debug_echo("appel yyparse, Ctrl+D pour arrêter la saisie");
	yyparse();
	debug_echo("fin yyparse");
	
	debug_echo("libérations et fin...");
	sanitizer();

  return EXIT_SUCCESS;

}
