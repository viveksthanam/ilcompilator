/*code des routines de traitement*/
//% vim: ts=2 tw=80
#include <iostream>
#include <cstdlib>
#include "process.h"
#include "debug.h"
#include "declarationqueue.h"
#include "instructionqueue.h"
#include "contextstack.h"
#include "stringid.h"
#include "type.h"

using namespace std;

extern int current_decl_type;
extern int yyerror(char *s);
extern int current_decl_type;
extern CContextStack* CS_main;
extern CDeclarationQueue* DQ_main;
extern CInstructionQueue* IQ_main;

extern void sanitizer (void);

/** \file process.cpp
* \brief Corps des fonctions de traitement
* \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
* \version
* \date 07/12/2007
*/

int process_declaration(int arg1, int arg2) {

   CSymbol* retval = NULL;

  //debug_echo("declaration: type id_aff_list PV");

	if (current_decl_type != -1) {
  
    //empilement du symbole sur la CS
    retval = CS_main->addSymbol( CStringID( arg2 ), CType( (TYPEVAL)arg1 , 0 ) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a échoué, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	  
     debug_echoi( "Symbole créé à l'adresse:", (int)retval );
    
    //instruction de déclaration 
    DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)arg1 , 0 ) ); 
    debug_echo("déclaration du symbole empilée");

	}
	else {
		debug_critical("debut de déclaration inattendue");
		return EXIT_FAILURE; 
	}
  
  	return ((int)retval);

}

int process_declaration_end() {

	if (current_decl_type != -1) {
		debug_echo("Fin de déclaration, repositionne current_decl_type à -1");	
	  current_decl_type = -1;
  }
	else { 
		debug_critical("fin de déclaration inattendue");
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

  //on se trouve dans les déclarations
  if ( current_decl_type != -1 ) {
    debug_echoi("ID, son TinyStringID vaut:", tinystrid);
    return tinystrid; 
  }

  //on se trouve dans les instructions
  else {

    retval = current_CS->getSymbolInContext( CStringID( tinystrid ) );

    if ( !retval )  
      debug_critical_exit( "Symbole non trouvé dans le contexte.", sanitizer );   
    else {
      debug_echoi( "Symbole trouvé dans le contexte à l'adresse:", (int)retval );  
      return ((int)retval);
    }

  }

  return EXIT_FAILURE; //should not happen <fear!>

}

int process_context_open() {

  debug_echo("contexte ouvert");
  CS_main->saveContext();

  return EXIT_SUCCESS;
}

int process_context_save() {

  debug_echo("contexte sauvé");
  CS_main->saveContext();

  return EXIT_SUCCESS;
}

int process_int ( int val ) {
 
  CSymbol* retval = NULL;
  CInstruction* instr = NULL;

  retval = CS_main->addSymbol( CStringID(), CType( T_INT , 0 ) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a échoué, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
  debug_echoi( "Symbole INT créé à l'adresse:", (int)retval );

  //creation declaration + instruction affectation
  DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)T_INT , 0 ) ); 
  debug_echo("déclaration du symbole empilée");
  
  instr = new CInstruction( retval, (float)val );
  if (!instr) debug_critical_exit("échec de la création d'instruction", sanitizer);
  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'affectation empilée");

  return ((int)retval);

}

int process_float ( float val ) {
  
  CSymbol* retval = NULL;
  CInstruction* instr = NULL;
  
  retval = CS_main->addSymbol( CStringID(), CType( T_FLOAT , 0 ) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a échoué, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
  debug_echoi( "Symbole FLOAT créé à l'adresse:", (int)retval );

  //creation declaration + instruction affectation
  DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)T_FLOAT , 0 ) ); 
  debug_echo("déclaration du symbole empilée");
  
  instr = new CInstruction( retval, val );
  if (!instr) debug_critical_exit("échec de la création d'instruction", sanitizer);
  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'affectation empilée");
 
  return ((int)retval);
}

int process_bool ( int val ) {
   
  CSymbol* retval = NULL;
  CInstruction* instr = NULL;
  
  retval = CS_main->addSymbol( CStringID(), CType( T_BOOL , 0 ) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a échoué, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
  debug_echoi( "Symbole BOOL créé à l'adresse:", (int)retval );

  //creation declaration + instruction affectation
  DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)T_BOOL , 0 ) ); 
  debug_echo("déclaration du symbole empilée");

  instr = new CInstruction( retval, (float)val );
  if (!instr) debug_critical_exit("échec de la création d'instruction", sanitizer);
  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'affectation empilée");

  return ((int)retval);
}

int process_assignment(int arg1, int arg3) {
  
  CInstruction* instr = NULL;
  bool cast_state;

  if ( !(arg1) || !(arg3) )
    debug_critical_exit("assignation avec (au moins) un symbole invalide sur deux", sanitizer);
  
  debug_echoi("assigne à $1, situé à",arg1);
  debug_echoi("la donnée dans $3, située à",arg3); 
  
  /*instr = new CInstruction( (Operator)OP2_EQU, 
                            (SymbolID)( ((CSymbol*)arg1)->getID() ), 
                            (SymbolID)( ((CSymbol*)arg3)->getID() ), 
                            INVALID_SYMBOL, 
                            CType( (TYPEVAL)T_INVALID , 0 ) 
                          );*/
 
  instr = new CInstruction( (CSymbol*)arg1, (CSymbol*)arg3 );

  if (!instr) debug_critical_exit("échec de la création d'instruction", sanitizer);
  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'assignement empilée");
    
  return EXIT_SUCCESS;
}

int process_plus(int arg1, int arg3) {

  CSymbol* retval = NULL;
  CInstruction* instr = NULL;
  
  if ( !(arg1) || !(arg3) )
    debug_critical_exit("addition avec (au moins) un symbole invalide sur deux", sanitizer);
  
  debug_echo("PLUS");
  debug_echoi("$1 à l'adresse:", (int)arg1);
  debug_echoi("$3 à l'adresse:", (int)arg3);

  //retval = CS_main->addSymbol( CStringID(), CType( T_FLOAT , 0 ) );

  /*instr = new CInstruction( (Operator)OP3_ADD, 
                            cible
                            (SymbolID)( ((CSymbol*)arg1)->getID() ), 
                            (SymbolID)( ((CSymbol*)arg3)->getID() ), 
                            CType( (TYPEVAL)T_INVALID , 0 ) 
                          );*/
  
  return EXIT_SUCCESS;
}























/*A traiter:*/

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
 
int process_uop_moins(int arg1, int arg2) {

  debug_echo("MOINS exp %prec MUNAIRE");
  return EXIT_SUCCESS;
}

int process_uop_not(int arg1, int arg2) {

  debug_echo("NOT exp %prec MUNAIRE");
  return EXIT_SUCCESS;
}

int process_uop_star(int arg1, int arg2) {

  debug_echo("STAR exp %prec MUNAIRE");
  return EXIT_SUCCESS;
}

/* fin process.cpp */
