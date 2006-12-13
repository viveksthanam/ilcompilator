//% vim: tw=80 ts=2

%{

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "y.tab.h"
#include "codewriter.h"
#include "instructionqueue.h"
#include "declarationqueue.h"
#include "configuration.h"
#include "process.h"
#include "debug.h"
#include "type.h"
#include "hashtable.h"
#include "contextstack.h"

/** \addtogroup YaccInitInstructions
* Fonctions, variables et commandes du préprocesseur paramétrant Yacc.
* @{
*/

/** \brief Ajouté car ne compilait pas avec g++.
*/
int yylex (void);

/** \brief Variables globales servant d'interface entre Lex et Yacc.
*/
int yyval=0;
int yyval_int=0;
float yyval_float=0.0;

using namespace std;

/** \brief Initialisation a NULL permettant d'effectuer des tests et de compiler
 * sans erreur, allocation dynamique au debut de main().
*/
CHashtable* HT_main = NULL;

/** \brief Idem HT_main.
*/
CContextStack* CS_main = NULL;

/** \brief Idem DQ_main.
*/
CDeclarationQueue* DQ_main = NULL;

/** \brief Idem IQ_main.
*/
CInstructionQueue* IQ_main = NULL;

/** \brief Idem CW_main
*/
CCodeWriter* CW_main = NULL; 

/** \brief Variable globale conservant le type des ou de la dernière variable à 
 * déclarer, -1 voulant dire qu'il n'y a plus de variables à declarer pour
 * l'instruction courante.
*/ 
int current_decl_type = -1; 

/** \brief Etat du debug: 0 (défaut), ou 1 pour activer. Deux niveaux par
 * défaut, on pourra étendre par la suite.
*/
extern int debug_level;

/** \brief Libère les ressources utilisées par nos piles.
 */
void sanitizer (void) {

delete CS_main;
delete HT_main;
delete DQ_main;
delete IQ_main;

}

/** @} */

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

pv : PV { } 
     | ;

decl_list : decl_list decl { } 
            | ;

decl : type id_aff_list PV { process_declaration_end(); } ; 

id_aff_list : id_aff_list VIR id_aff { $$ = process_declaration(current_decl_type,$3); } 
              | id_aff               { $$ = process_declaration(current_decl_type,$1); }

id_aff : id       { $$ = $1; }
         | affect { $$ = $1; };

id : ID { $$ = process_id($1,CS_main); };

type : INT         { $$ = process_type(T_INT); }
       | FLOAT     { $$ = process_type(T_FLOAT); } 
       | BOOL      { $$ = process_type(T_BOOL); }
       | type STAR { };

inst_list : inst_list PV inst { }
            | inst            { };

inst : affect { }
       | cond { debug_echo("cond"); }
       | loop { debug_echo("loop"); }
       | bloc { };

affect : id EQ exp { $$ = process_assignment($1,$3); };

cond : IF exp THEN inst             { }
       | IF exp THEN inst ELSE inst { };

loop : while exp_do inst       { process_while_end($1,$2); }
       | repeat inst UNTIL exp { process_repeat_end($1,$4); };

while: WHILE { process_while_begin(); };

exp_do: exp DO { process_exp_do_begin($1); };

repeat: REPEAT { process_repeat_begin(); };

bloc : da prog fa { $$=$2; };
da : DA           { process_context_open(); };
fa : FA           { process_context_save(); };

exp :  exp OR exp            { process_or($1,$3); }
     | exp AND exp           { process_and($1,$3); }
     | exp PLUS exp          { process_plus($1,$3); }
     | exp MOINS exp         { process_moins($1,$3); }
     | exp STAR exp          { process_star($1,$3); }
     | exp DIV exp           { process_div($1,$3); }
     | exp EQL exp           { process_eql($1,$3); }
     | exp GRT exp           { process_grt($1,$3); }
     | exp LOW exp           { process_low($1,$3); }
     | exp NEQ exp           { process_neq($1,$3); }
     | uop exp %prec MUNAIRE { process_uop($1,$2); }
     | DP exp FP             { $$ = $2; }
     | id                    { $$ = $1; }
     | const                 { $$ = $1; }; 

const : NUM_I   { $$ = process_int( yyval_int ); }
        | NUM_F { $$ = process_float( yyval_float ); }
        | TRUE  { $$ = process_bool( DEF_TRUE ); }
        | FALSE { $$ = process_bool( DEF_FALSE ); };

uop : STAR    { $$ = $1; }
      | MOINS { $$ = $1; }
      | NOT   { $$ = $1; };

%%
  
int main( int argc, char** argv )
{
	
  about(); 
	debug_set_level( &argc, argv );

  debug_echo("creation HashTable principale");
	HT_main = new CHashtable;

 	debug_echo("création ContextStack principale");
	CS_main = new CContextStack;

	debug_echo("création DeclarationQueue principale");
	DQ_main = new CDeclarationQueue;

  debug_echo("création InstructionQueue principale");
  IQ_main = new CInstructionQueue;

  debug_echo("création CodeWriter principal");
  CW_main = new CCodeWriter(NULL);

	debug_echo("appel yyparse(), Ctrl+D pour arrêter la saisie");
	yyparse();

  debug_echo("production des déclarations");
  CW_main->writeDeclarations( DQ_main ); 

  debug_echo("production des instructions");
  CW_main->writeInstructions( IQ_main );

	debug_echo("libérations et fin...");
	sanitizer();

  return EXIT_SUCCESS;

}
