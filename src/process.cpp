/*code des routines de traitement*/
//% vim: ts=2 tw=80

/** \file process.cpp
* \brief Corps des fonctions de traitement de projet.y.
* \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
* \version
* \date 07/12/2007
*/

#include <iostream>
#include <cstdlib>

#include "process.h"
#include "debug.h"
#include "declarationqueue.h"
#include "instructionqueue.h"
#include "contextstack.h"
#include "stringid.h"
#include "type.h"
#include "label.h"

using namespace std;

extern int current_decl_type;
extern int yyerror(char *s);
extern int current_decl_type;
extern CContextStack* CS_main;
extern CDeclarationQueue* DQ_main;
extern CInstructionQueue* IQ_main;
extern CLabel* LB_main;

extern void sanitizer (void);

int process_declaration(int arg1, int arg2, int ref_level) {

   CSymbol* retval = NULL;

  //debug_echo("declaration: type id_aff_list PV");

	if (current_decl_type != -1) {
    
    debug_echo("<déclaration>");
  
    //vérification que le StringID n'est pas déjà 
    //présent dans le contexte courant
    if ( CS_main->getSymbolInContext( CStringID(arg2) ) ) 
      debug_critical_exit("StringID déjà rencontrée dans le contexte courant", sanitizer);

    //empilement du symbole sur la CS
    retval = CS_main->addSymbol( CStringID( arg2 ), CType( (TYPEVAL)arg1 ,ref_level ) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a échoué, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	  
     debug_echoi( "Symbole créé à l'adresse:", (int)retval );
     debug_echoi( "Niveau de référencement:",ref_level);
    
    //instruction de déclaration 
    DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)arg1 , ref_level) ); 
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
		debug_echo("</déclaration>");	
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

  if ( !current_CS )
    debug_critical_exit("pointeur sur CS nul", sanitizer );
  
  //on se trouve dans les déclarations
  if ( current_decl_type != -1 ) {
    debug_echoi("ID, son TinyStringID vaut:", tinystrid);
    return tinystrid; 
  }

  //on se trouve dans les instructions
  else {

    retval = current_CS->getSymbolInContext( CStringID( tinystrid ) );

    if ( !retval ) {
    
      debug_echo("Symbole non trouvé dans le contexte, recherche hors du contexte...");   
      retval = current_CS->getSymbol( CStringID( tinystrid ) ); 
      if ( !retval ) debug_critical_exit("symbole non trouvé dans la CS", sanitizer);
      debug_echoi("Symbole trouvé hors du contexte à l'adresse:", (int)retval);
      return ((int)retval);
    }
   
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
  CS_main->restoreContext();

  return EXIT_SUCCESS;
}

int process_int ( int val ) {
 
  CSymbol* retval = NULL;
  CInstruction* instr = NULL;

  retval = CS_main->addSymbol( CStringID(), CType( T_INT , DEFAULT_REF_LVL) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a échoué, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
  debug_echoi( "Symbole INT créé à l'adresse:", (int)retval );

  //creation declaration + instruction affectation
  DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)T_INT , DEFAULT_REF_LVL) ); 
  debug_echo("déclaration du symbole empilée");
  
  instr = new CInstruction( retval, (float)val );

  if (!instr)
  {
    debug_critical_exit("échec de la création d'instruction", sanitizer);
  }

  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'affectation empilée");

  return ((int)retval);

}

int process_float ( float val ) {
  
  CSymbol* retval = NULL;
  CInstruction* instr = NULL;
  
  retval = CS_main->addSymbol( CStringID(), CType( T_FLOAT , DEFAULT_REF_LVL) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a échoué, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
  debug_echoi( "Symbole FLOAT créé à l'adresse:", (int)retval );

  //creation declaration + instruction affectation
  DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)T_FLOAT , DEFAULT_REF_LVL) ); 
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
  
  retval = CS_main->addSymbol( CStringID(), CType( T_BOOL , DEFAULT_REF_LVL) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a échoué, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
  debug_echoi( "Symbole BOOL créé à l'adresse:", (int)retval );

  //creation declaration + instruction affectation
  DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)T_BOOL , DEFAULT_REF_LVL) ); 
  debug_echo("déclaration du symbole empilée");

  instr = new CInstruction( retval, (float)val );
  if (!instr) debug_critical_exit("échec de la création d'instruction", sanitizer);
  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'affectation empilée");

  return ((int)retval);
}

int process_assignment(int arg1, int arg3) {
  
  CInstruction* instr = NULL;

  if ( !(arg1) || !(arg3) )
    debug_critical_exit("assignation avec (au moins) un symbole invalide sur deux", sanitizer);
 
  if ( current_decl_type != -1 )
    debug_critical_exit("tentative d'assignation durant une phase de déclaration", sanitizer);

  debug_echoi("assigne à $1, situé à",arg1);
  debug_echoi("la donnée dans $3, située à",arg3); 
  
  /* debug avancé inutile car fonctionne au poil
  debug_echoi("type de $1", (int)(((CSymbol*)arg1)->getType()).getTypeVal() );
  debug_echoi("type de $3", (int)(((CSymbol*)arg3)->getType()).getTypeVal() );
  debug_echoi("ref lvl de $1", (int)(((CSymbol*)arg1)->getType()).getRef() );
  debug_echoi("ref lvl de $3", (int)(((CSymbol*)arg3)->getType()).getRef() );
  */

  instr = new CInstruction( (CSymbol*)arg1, (CSymbol*)arg3 );

  if (!instr) debug_critical_exit("échec de la création d'instruction", sanitizer);
  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'assignement empilée");
    
  return EXIT_SUCCESS;
}

int process_op3(int arg1, int arg3, Operator oprtr) {

  CType type_compatible; 
  CType type_arg1;
  CType type_arg3;
  CSymbol* retval = NULL;
  CInstruction* instr = NULL;

  bool a,b;
  
  if ( !(arg1) || !(arg3) )
    debug_critical_exit("opération avec (au moins) un symbole invalide sur deux", sanitizer);
  
  debug_echoi("opération: $1 à l'adresse:", (int)arg1);
  debug_echoi("opération: $3 à l'adresse:", (int)arg3);

  //trouve le type de retour compatible avec ceux des arguments
  type_arg1 = ((CSymbol*)arg1)->getType();
  type_arg3 = ((CSymbol*)arg3)->getType();

  // Mes deux opérandes sont elles des pointeurs ?
  if( (type_arg1.getRef() > 0) && (type_arg3.getRef() > 0) )
  {
    // L'opération est elle autre chose qu'une soustraction OU/ET les opérandes
    // sont elles de type différents ?
    if( (oprtr != OP3_SUB)
      || (type_arg1.getTypeVal() != type_arg3.getTypeVal()) ) 
      debug_critical_exit("Opération invalide sur un pointeur",sanitizer);
  }
  else
  {
    // Résumé de l'épisode : A ce point on sait que les opérandes ne sont
    // toutes les deux des pointeurs.

    // Il y a t'il une opérande qui soit un pointeur ?
    // (on stocke laquelle des deux est le pointeur en question grâce à
    // a et b)
    if( (a=(type_arg1.getRef() > 0)) || (b=(type_arg3.getRef() > 0)) )
    {
      // L'opération est elle autre que l'addition ou la soustraction ?
      if( oprtr != OP3_ADD && oprtr != OP3_OR )
        debug_critical_exit("Opération invalide sur un pointeur",sanitizer);
      
      // Un petit hack ici pour exprimer de manière compacte :
      // L'opérande qui n'est pas un pointeur est elle du type INT ?
      if( !( ( b && (type_arg1.getTypeVal() == T_INT))
          || ( a && (type_arg3.getTypeVal() == T_INT)) ) )
      {
      
        // L'opération est elle l'addition ?
        if( oprtr == OP3_ADD )
          debug_critical_exit("L'addition d'un pointeur est uniquement autorisée\
avec un entier",sanitizer);
        else
          debug_critical_exit("La soustraction d'un pointeur est uniquement\
autorisée avec un entier",sanitizer);

      }

    }

  }


  type_compatible = type_arg1.returnCompatible( type_arg3 ); 
  debug_echoi("Type de retour compatible trouvé:", type_compatible.getTypeVal());

  //cree le symbole de retour
  retval = CS_main->addSymbol( CStringID(), type_compatible ) ;
  debug_echoi("Symbole de retour pour l'opération créé à l'adresse:", (int)retval);
	
  //creation declaration pour le symbole de retour
  DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)type_compatible.getTypeVal() , DEFAULT_REF_LVL) ); 
  debug_echo("Déclaration du symbole de retour empilée");

  instr = new CInstruction( oprtr,
                            (CSymbol*) retval,
                            (CSymbol*) arg1,
                            (CSymbol*) arg3 
                          );

  if ( !instr->isValid() ) 
    debug_critical_exit("le constructeur d'instruction employé ne correspond pas à l'opérateur utilisé", sanitizer);
 
  //empilement
  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'opération valide et empilée");
    
  return ((int)retval);
}

int process_op3_bool(int arg1, int arg3, Operator oprtr) {

  CType type_compatible; 
  CType type_arg1;
  CType type_arg3;
  int arg1_type_val = -1;
  int arg3_type_val = -1;
  CSymbol* retval = NULL;
  CInstruction* instr = NULL;
  // en cas d'arg1 ou arg3 non booléens
  CSymbol* arg1bool = NULL;
  CInstruction* arg1boolcast_instr = NULL;
  CSymbol* arg3bool = NULL;
  CInstruction* arg3boolcast_instr = NULL;

  if ( !(arg1) || !(arg3) )
    debug_critical_exit("opération avec (au moins) un symbole invalide sur deux", sanitizer);
  
  debug_echoi("opération: $1 à l'adresse:", (int)arg1);
  debug_echoi("opération: $3 à l'adresse:", (int)arg3);

  //gestion des types des arguments
  arg1_type_val = ((CSymbol*)arg1)->getType().getTypeVal();
  arg3_type_val = ((CSymbol*)arg3)->getType().getTypeVal();
 
  
  //gestion si symboles incompatibles
  if ( arg1_type_val != (TYPEVAL)T_BOOL ) {
    //some more code...   
    debug_echo("<cast de $1 en bool>");
    debug_echoi("$1 n'est pas de type BOOL, $1 est de type:", arg1_type_val);
    arg1bool = CS_main->addSymbol( CStringID(), CType( (TYPEVAL)T_BOOL, DEFAULT_REF_LVL) ) ; 
    debug_echoi("Symbole destiné à recevoir le cast en booléen de $1 créé à l'adresse:",(int)arg1bool);
    DQ_main->addDeclaration( arg1bool->getID(), CType( (TYPEVAL)T_BOOL, DEFAULT_REF_LVL) ); 
    debug_echo("déclaration du symbole booléen du cast de $1 empilée");
    arg1boolcast_instr = new CInstruction ( (CSymbol*)arg1bool, (CSymbol*)arg1 );
    if ( !arg1boolcast_instr->isValid() ) 
    debug_critical_exit("le constructeur d'instruction du cast de $1 a échoué ", sanitizer);
    IQ_main->pushInstruction( arg1boolcast_instr );
    debug_echo("instruction d'opération booléenne sur $1 valide et empilée");
    arg1 = (int)arg1bool;
    debug_echo("</cast de $1 en bool>");
 
  }
 
  if ( arg3_type_val != (TYPEVAL)T_BOOL ) {
    //some more code... 
    debug_echo("<cast de $3 en bool>"); 
    debug_echoi("$3 n'est pas de type BOOL, $3 est de type:", arg3_type_val);
    arg3bool = CS_main->addSymbol( CStringID(), CType( (TYPEVAL)T_BOOL, DEFAULT_REF_LVL) );
    debug_echoi("Symbole destiné à recevoir le cast en booléen de $3 créé à l'adresse:",(int)arg3bool);   
    DQ_main->addDeclaration( arg3bool->getID(), CType( (TYPEVAL)T_BOOL, DEFAULT_REF_LVL) ); 
    debug_echo("déclaration du symbole booléen du cast de $3 empilée");
    arg3boolcast_instr = new CInstruction ( (CSymbol*)arg3bool, (CSymbol*)arg3 );
    if ( !arg3boolcast_instr->isValid() ) 
    debug_critical_exit("le constructeur d'instruction du cast de $3 a échoué ", sanitizer);
    IQ_main->pushInstruction( arg3boolcast_instr );
    debug_echo("instruction d'opération booléenne sur $3 valide et empilée");
    arg3 = (int)arg3bool;  
    debug_echo("</cast de $3 en bool>");

  }
    
  //cree le symbole de retour de type bool
  retval = CS_main->addSymbol( CStringID(), CType( (TYPEVAL)T_BOOL, DEFAULT_REF_LVL) ) ;
  debug_echoi("symbole de retour pour l'opération booléenne créé à l'adresse:", (int)retval);
	
  //creation declaration pour le symbole booléen de retour
  DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)T_BOOL, DEFAULT_REF_LVL) ); 
  debug_echo("déclaration du symbole booléen de retour empilée");

  instr = new CInstruction( oprtr,
                            (CSymbol*) retval,
                            (CSymbol*) arg1,
                            (CSymbol*) arg3 
                          );

  if ( !instr->isValid() ) 
    debug_critical_exit("le constructeur d'instruction employé ne correspond pas à l'opérateur booléen utilisé", sanitizer);
 
  //empilement
  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'opération booléenne valide et empilée");
    
  return ((int)retval);
}

int process_plus(int arg1, int arg3) {

  int pointeur = 0;
  debug_echo("<process plus>");
  pointeur = process_op3(arg1, arg3, OP3_ADD);
  if (!pointeur) debug_critical_exit("échec de process_plus",sanitizer); 
  debug_echo("</process plus>");
  return pointeur;
    
}

int process_moins(int arg1, int arg3) {

  int pointeur = 0;
  debug_echo("<process moins>");
  pointeur = process_op3(arg1, arg3, OP3_SUB);
  if (!pointeur) debug_critical_exit("échec de process_moins",sanitizer); 
  debug_echo("</process moins>");
  return pointeur;

}

int process_star(int arg1, int arg3) {

  int pointeur = 0;
  debug_echo("<process star>");
  pointeur = process_op3(arg1, arg3, OP3_MUL);
  if (!pointeur) debug_critical_exit("échec de process_star",sanitizer); 
  debug_echo("</process star>");
  return pointeur;

}

int process_div(int arg1, int arg3) {

  int pointeur = 0;
  debug_echo("<process div>");
  pointeur = process_op3(arg1, arg3, OP3_DIV);
  if (!pointeur) debug_critical_exit("échec de process_div",sanitizer); 
  debug_echo("</process div>");
  return pointeur;

}

 int process_bool_or(int arg1, int arg3) {
  
  int pointeur = 0;
  debug_echo("<process or>");
  pointeur = process_op3_bool(arg1, arg3, OP3_OR);
  if (!pointeur) debug_critical_exit("échec de process_bool_or",sanitizer); 
  debug_echo("</process or>");
  return pointeur;

} 

int process_bool_and(int arg1, int arg3) {
 
  int pointeur = 0;
  debug_echo("<process and>");
  pointeur = process_op3_bool(arg1, arg3, OP3_AND);
  if (!pointeur) debug_critical_exit("échec de process_bool_and",sanitizer); 
  debug_echo("</process and>");
  return pointeur;

}

int process_bool_eql(int arg1, int arg3) {
  
  int pointeur = 0;
  debug_echo("<process eql>");
  pointeur = process_op3_bool(arg1, arg3, OP3_EQL);
  if (!pointeur) debug_critical_exit("échec de process_bool_eql",sanitizer); 
  debug_echo("</process eql>");
  return pointeur;

}

int process_grt(int arg1, int arg3) {
  
  int pointeur = 0;
  debug_echo("<process grt>");
  pointeur = process_op3(arg1, arg3, OP3_GRT);
  if (!pointeur) debug_critical_exit("échec de process_bool_grt",sanitizer); 
  debug_echo("</process grt>");
  return pointeur;

}

int process_low(int arg1, int arg3) {
  
  int pointeur = 0;
  debug_echo("<process low>");
  pointeur = process_op3(arg1, arg3, OP3_LOW);
  if (!pointeur) debug_critical_exit("échec de process_bool_low",sanitizer); 
  debug_echo("</process low>");
  return pointeur;

}

int process_bool_neq(int arg1, int arg3) {
  
  int pointeur = 0;
  debug_echo("<process neq>");
  pointeur = process_op3_bool(arg1, arg3, OP3_NEQ);
  if (!pointeur) debug_critical_exit("échec de process_bool_neq",sanitizer); 
  debug_echo("</process neq>");
  return pointeur;

}

int process_if(int arg1)
{

  LB_main->push();

  CType type(T_BOOL,0);

  CSymbol* symbol = CS_main->addSymbol( CStringID(), type );

  CInstruction* p_instr =
    new CInstruction( OP2_NOT, symbol, (CSymbol*)arg1 );

  // <2> = !<1>
  DQ_main->addDeclaration( symbol->getID(), symbol->getType() );
  IQ_main->pushInstruction( p_instr );
  
  p_instr = 
    new CInstruction( OP2_IF, LB_main->getThen(), symbol);

  // if <2> goto <label>
  IQ_main->pushInstruction( p_instr ); 


  return EXIT_SUCCESS;

}

int process_then()
{

  CInstruction* p_instr = 
    new CInstruction( OP1_LABEL, LB_main->getThen());

  // <label>:
  IQ_main->pushInstruction( p_instr ); 

  LB_main->pop();

  return EXIT_SUCCESS;

}

int process_else()
{

  CInstruction* p_instr = 
    new CInstruction( OP1_GOTO, LB_main->getElse() );

  // goto <label>;
  IQ_main->pushInstruction( p_instr ); 

  p_instr = 
    new CInstruction( OP1_LABEL, LB_main->getThen() );

  // label:
  IQ_main->pushInstruction( p_instr ); 

  return EXIT_SUCCESS;

}

int process_fin_else()
{

  CInstruction* p_instr = 
    new CInstruction( OP1_LABEL, LB_main->getElse());

  // label:
  IQ_main->pushInstruction( p_instr ); 

  LB_main->pop();

  return EXIT_SUCCESS;

};

int process_while_end(int arg1) {

  CInstruction* p_instr = 
    new CInstruction( OP2_IF, LB_main->getThen(), (CSymbol*)arg1);

  // if <2> goto <label>
  IQ_main->pushInstruction( p_instr ); 

  LB_main->pop();

  return EXIT_SUCCESS;

}

int process_repeat_end(int arg4) {

  CInstruction* p_instr = 
    new CInstruction( OP2_IF, LB_main->getThen(), (CSymbol*)arg4 );

  // if <2> goto <label>
  IQ_main->pushInstruction( p_instr ); 

  LB_main->pop();

  return EXIT_SUCCESS;

}

int process_while_begin() {

  LB_main->push();

  CInstruction* p_instr = 
    new CInstruction( OP1_LABEL, LB_main->getThen() );

  // label:
  IQ_main->pushInstruction( p_instr ); 

  return EXIT_SUCCESS;

}

int process_exp_do_begin(int arg1) {

  //cerr<<arg1<<endl;

  return arg1;

}

int process_repeat_begin() {

  LB_main->push();

  CInstruction* p_instr = 
    new CInstruction( OP1_LABEL, LB_main->getThen() );

  // label:
  IQ_main->pushInstruction( p_instr ); 

  return EXIT_SUCCESS;

}

int process_uop_star(int arg1, int arg2) {

  int ref_level = ((CSymbol*)arg2)->getType().getRef();
  TYPEVAL typeval = ((CSymbol*)arg2)->getType().getTypeVal();

  if( ref_level == 0 )
    debug_critical("impossible de déréférencer la variable");

  CSymbol* symbol = CS_main->addSymbol( CStringID(),
                                       CType( typeval, ref_level-1));

  CInstruction* p_instr =
    new CInstruction( OP2_STAR, symbol, (CSymbol*)arg2 );

  // <2> = *<1>
  DQ_main->addDeclaration( symbol->getID(), symbol->getType() );
  IQ_main->pushInstruction( p_instr );
 
  return (int)symbol;
}


int process_uop_cast(int arg1, int arg4, int ref_level)
{
  CType type( (TYPEVAL)arg1, ref_level);

  if( (ref_level == 0)  && (((CSymbol*)arg4)->getType().getRef() == 0))
    if( !(((CSymbol*)arg4)->getType().canConvertTo( type )) )
    {
      debug_critical("Pertes de données lors du cast.");
    }

  CSymbol* symbol = CS_main->addSymbol( CStringID(),
                                        type );

  CInstruction* p_instr = 
    new CInstruction( symbol, (CSymbol*)arg4);
 
  // <1> = (<3>)<2>
  DQ_main->addDeclaration( symbol->getID(), symbol->getType() );
  IQ_main->pushInstruction( p_instr );
  
  return (int)symbol;

} 

/*A traiter:*/

int process_uop_moins(int arg1, int arg2) {

  debug_echo("MOINS exp %prec MUNAIRE");
  return EXIT_SUCCESS;
}

int process_uop_not(int arg1, int arg2) {

  debug_echo("NOT exp %prec MUNAIRE");
  return EXIT_SUCCESS;
}
/* fin process.cpp */
