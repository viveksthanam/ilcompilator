/*code des routines de traitement*/
//% vim: ts=2 tw=80
#include <iostream>
#include <cstdlib>
#include "process.h"
#include "debug.h"
#include "contextstack.h"
#include "stringid.h"

using namespace std;

extern int yyerror(char *s);
extern int current_decl_type;
extern CContextStack* CS_main;

/** \file process.cpp
* \brief Corps des fonctions de traitement
* \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
* \version
* \date 07/12/2007
*/

int process_declaration(int arg1, int arg2) {

	//current_decl_type = -1;
  debug_echo("declaration: type id_aff_list PV");

	if (current_decl_type != -1) {
  
		debug_echoi( "type symbole", arg1 );
		debug_echoi( "id_aff (string id du symbole)", arg2 ); 
		
		if ( !CS_main->addSymbol( CStringID( arg2 ), CType( (TYPEVAL)arg1 , 0 ) ) ) {
			debug_critical("l'allocation du symbole a �chou�, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
	}
	else {
		debug_critical("debut de d�claration inattendue");
		return EXIT_FAILURE; 
	}
  
	return EXIT_SUCCESS;
}

int process_declaration_end() {

	debug_echo("declaration_end, current_decl_type=-1");	
	if (current_decl_type != -1)
		current_decl_type = -1;
	else { 
		debug_critical("fin de d�claration inattendue");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
		
}

int process_assignment(int arg1, int arg3) {

  debug_echo("assignment: id EQ exp");
  return EXIT_SUCCESS;
}

int process_while_end(int arg1, int arg2) {

  debug_echo("while_end: while exp_do inst");
  return EXIT_SUCCESS;
}

int process_repeat_end(int arg1, int arg4) {

  debug_echo("repeat_end: repeat inst UNTIL exp");
  return EXIT_SUCCESS;
}

int process_while_begin() {

  debug_echo("while_begin: WHILE");
  return EXIT_SUCCESS;
}

int process_exp_do_begin(int arg1) {

  debug_echo("exp_do_begin: exp DO");
  return EXIT_SUCCESS;
}

int process_repeat_begin() {

  debug_echo("repeat_begin: REPEAT");
  return EXIT_SUCCESS;
}

int process_context_open() {

  debug_echo("context_open: DA");
  return EXIT_SUCCESS;
}

int process_context_save() {

  debug_echo("context_save: FA");
  return EXIT_SUCCESS;
}

int process_or(int arg1, int arg3) {

  debug_echo("or: exp OR exp");
  return EXIT_SUCCESS;
} 

int process_and(int arg1, int arg3) {

  debug_echo("and: exp AND exp");
  return EXIT_SUCCESS;
}

int process_plus(int arg1, int arg3) {

  debug_echo("plus: exp PLUS exp");
  return EXIT_SUCCESS;
}

int process_moins(int arg1, int arg3) {

  debug_echo("moins: exp MOINS exp");
  return EXIT_SUCCESS;
}

int process_star(int arg1, int arg3) {

  debug_echo("star: exp STAR exp");
  return EXIT_SUCCESS;
}

int process_div(int arg1, int arg3) {

  debug_echo("div: exp DIV exp");
  return EXIT_SUCCESS;
}

int process_eql(int arg1, int arg3) {

  debug_echo("eql: exp EQL exp");
  return EXIT_SUCCESS;
}

int process_grt(int arg1, int arg3) {

  debug_echo("grt: exp GRT exp");
  return EXIT_SUCCESS;
}

int process_low(int arg1, int arg3) {

  debug_echo("low: exp LOW exp");
  return EXIT_SUCCESS;
}

int process_neq(int arg1, int arg3) {

  debug_echo("neq: exp NEQ exp");
  return EXIT_SUCCESS;
}
 
int process_uop(int arg1, int arg2) {

  debug_echo("uop: uop exp %prec MUNAIRE");
  return EXIT_SUCCESS;
}

/* fin process.cpp */