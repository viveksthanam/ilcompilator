/*code des routines de traitement*/
//% vim: ts=2 tw=80
#include <iostream>
#include <cstdlib>
#include "process.h"
#include "debug.h"
#include "contextstack.h"
#include "stringid.h"
#include "type.h"

using namespace std;

extern int current_decl_type;
extern int yyerror(char *s);
extern int current_decl_type;
extern CContextStack* CS_main;

extern void sanitizer (void);

/** \file process.cpp
* \brief Corps des fonctions de traitement
* \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
* \version
* \date 07/12/2007
*/

int process_declaration(int arg1, int arg2) {

   CSymbol* retval = NULL;

  debug_echo("declaration: type id_aff_list PV");

	if (current_decl_type != -1) {
  
    retval = CS_main->addSymbol( CStringID( arg2 ), CType( (TYPEVAL)arg1 , 0 ) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a �chou�, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
	}
	else {
		debug_critical("debut de d�claration inattendue");
		return EXIT_FAILURE; 
	}
  
  debug_echoi( "Symbole cr�� � l'adresse:", (int)retval );
	return ((int)retval);

}

int process_declaration_end() {

	if (current_decl_type != -1) {
		debug_echo("declaration_end, current_decl_type=-1");	
	  current_decl_type = -1;
  }
	else { 
		debug_critical("fin de d�claration inattendue");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
		
}

int process_type ( int type ) {

  if ( -1 == current_decl_type ) {
    debug_echoi( "Type du symbole:", type );
    current_decl_type = type;
    return (type);
  }
  else {
    debug_critical("type inattendu");
    return EXIT_FAILURE;
  }

}

int process_id ( int tinystrid, CContextStack* current_CS ) {

  CSymbol* retval = NULL;

  if ( (!tinystrid) || (!current_CS) )
    debug_critical_exit("TinyStringID vide ou pointeur sur CS nul", sanitizer );

  //on se trouve dans les d�clarations
  if ( current_decl_type != -1 ) {
    debug_echoi("ID, son TinyStringID vaut:", tinystrid);
    return tinystrid; 
  }

  //on se trouve dans les instructions
  else {

    retval = current_CS->getSymbolInContext( CStringID( tinystrid ) );

    if ( !retval )  
      debug_critical_exit( "Symbole non trouv� dans le contexte.", sanitizer );   
    else {
      debug_echoi( "Symbole trouv� dans le contexte � l'adresse:", (int)retval );  
      return ((int)retval);
    }

  }

  return EXIT_FAILURE; //should not happen <fear!>

}

int process_context_open() {

  debug_echo("context_open: DA");
  CS_main->saveContext();

  return EXIT_SUCCESS;
}

int process_context_save() {

  debug_echo("context_save: FA");
  CS_main->saveContext();

  return EXIT_SUCCESS;
}

int process_int ( int val ) {
 
  CSymbol* retval = NULL;

  retval = CS_main->addSymbol( CStringID(), CType( T_INT , 0 ) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a �chou�, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
  debug_echoi( "Symbole INT cr�� � l'adresse:", (int)retval );

  //creation instruction affectation
    
  return ((int)retval);
}

int process_float ( float val ) {
  
  CSymbol* retval = NULL;

  retval = CS_main->addSymbol( CStringID(), CType( T_FLOAT , 0 ) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a �chou�, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
  debug_echoi( "Symbole FLOAT cr�� � l'adresse:", (int)retval );

  //creation instruction affectation
    
  return ((int)retval);
}

int process_bool ( int val ) {
   
  CSymbol* retval = NULL;

  retval = CS_main->addSymbol( CStringID(), CType( T_BOOL , 0 ) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a �chou�, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
  debug_echoi( "Symbole BOOL cr�� � l'adresse:", (int)retval );

  //creation instruction affectation
    
  return ((int)retval);
}



















/*A traiter:*/

int process_assignment(int arg1, int arg3) {

  debug_echo("assignment: ID EQ exp");
  debug_echoi("assign $1",arg1);
  debug_echoi("assign $3",arg3); 
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
