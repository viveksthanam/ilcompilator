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
    
    debug_echo("<d�claration>");
  
    //v�rification que le StringID n'est pas d�j� 
    //pr�sent dans le contexte courant
    if ( CS_main->getSymbolInContext( CStringID(arg2) ) ) 
      debug_critical_exit("StringID d�j� rencontr�e dans le contexte courant", sanitizer);

    //empilement du symbole sur la CS
    retval = CS_main->addSymbol( CStringID( arg2 ), CType( (TYPEVAL)arg1 ,ref_level ) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a �chou�, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	  
     debug_echoi( "Symbole cr�� � l'adresse:", (int)retval );
     debug_echoi( "Niveau de r�f�rencement:",ref_level);
    
    //instruction de d�claration 
    DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)arg1 , ref_level) ); 
    debug_echo("d�claration du symbole empil�e");
	}
	else {
		debug_critical("debut de d�claration inattendue");
		return EXIT_FAILURE; 
	}
  
  	return ((int)retval);

}

int process_declaration_end() {

	if (current_decl_type != -1) {
		debug_echo("</d�claration>");	
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

  if ( !current_CS )
    debug_critical_exit("pointeur sur CS nul", sanitizer );
  
  //on se trouve dans les d�clarations
  if ( current_decl_type != -1 ) {
    debug_echoi("ID, son TinyStringID vaut:", tinystrid);
    return tinystrid; 
  }

  //on se trouve dans les instructions
  else {

    retval = current_CS->getSymbolInContext( CStringID( tinystrid ) );

    if ( !retval ) {
    
      debug_echo("Symbole non trouv� dans le contexte, recherche hors du contexte...");   
      retval = current_CS->getSymbol( CStringID( tinystrid ) ); 
      if ( !retval ) debug_critical_exit("symbole non trouv� dans la CS", sanitizer);
      debug_echoi("Symbole trouv� hors du contexte � l'adresse:", (int)retval);
      return ((int)retval);
    }
   
    else {
      debug_echoi( "Symbole trouv� dans le contexte � l'adresse:", (int)retval );  
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

  debug_echo("contexte sauv�");
  CS_main->restoreContext();

  return EXIT_SUCCESS;
}

int process_int ( int val ) {
 
  CSymbol* retval = NULL;
  CInstruction* instr = NULL;

  retval = CS_main->addSymbol( CStringID(), CType( T_INT , DEFAULT_REF_LVL) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a �chou�, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
  debug_echoi( "Symbole INT cr�� � l'adresse:", (int)retval );

  //creation declaration + instruction affectation
  DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)T_INT , DEFAULT_REF_LVL) ); 
  debug_echo("d�claration du symbole empil�e");
  
  instr = new CInstruction( retval, (float)val );

  if (!instr)
  {
    debug_critical_exit("�chec de la cr�ation d'instruction", sanitizer);
  }

  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'affectation empil�e");

  return ((int)retval);

}

int process_float ( float val ) {
  
  CSymbol* retval = NULL;
  CInstruction* instr = NULL;
  
  retval = CS_main->addSymbol( CStringID(), CType( T_FLOAT , DEFAULT_REF_LVL) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a �chou�, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
  debug_echoi( "Symbole FLOAT cr�� � l'adresse:", (int)retval );

  //creation declaration + instruction affectation
  DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)T_FLOAT , DEFAULT_REF_LVL) ); 
  debug_echo("d�claration du symbole empil�e");
  
  instr = new CInstruction( retval, val );
  if (!instr) debug_critical_exit("�chec de la cr�ation d'instruction", sanitizer);
  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'affectation empil�e");
 
  return ((int)retval);
}

int process_bool ( int val ) {
   
  CSymbol* retval = NULL;
  CInstruction* instr = NULL;
  
  retval = CS_main->addSymbol( CStringID(), CType( T_BOOL , DEFAULT_REF_LVL) );
		
    if ( !retval ) {
			debug_critical("l'allocation du symbole a �chou�, pas d'empilement sur la CS");
			return EXIT_FAILURE;
		}
	
  debug_echoi( "Symbole BOOL cr�� � l'adresse:", (int)retval );

  //creation declaration + instruction affectation
  DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)T_BOOL , DEFAULT_REF_LVL) ); 
  debug_echo("d�claration du symbole empil�e");

  instr = new CInstruction( retval, (float)val );
  if (!instr) debug_critical_exit("�chec de la cr�ation d'instruction", sanitizer);
  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'affectation empil�e");

  return ((int)retval);
}

int process_assignment(int arg1, int arg3) {
  
  CInstruction* instr = NULL;

  if ( !(arg1) || !(arg3) )
    debug_critical_exit("assignation avec (au moins) un symbole invalide sur deux", sanitizer);
 
  if ( current_decl_type != -1 )
    debug_critical_exit("tentative d'assignation durant une phase de d�claration", sanitizer);

  debug_echoi("assigne � $1, situ� �",arg1);
  debug_echoi("la donn�e dans $3, situ�e �",arg3); 
  
  /* debug avanc� inutile car fonctionne au poil
  debug_echoi("type de $1", (int)(((CSymbol*)arg1)->getType()).getTypeVal() );
  debug_echoi("type de $3", (int)(((CSymbol*)arg3)->getType()).getTypeVal() );
  debug_echoi("ref lvl de $1", (int)(((CSymbol*)arg1)->getType()).getRef() );
  debug_echoi("ref lvl de $3", (int)(((CSymbol*)arg3)->getType()).getRef() );
  */

  instr = new CInstruction( (CSymbol*)arg1, (CSymbol*)arg3 );

  if (!instr) debug_critical_exit("�chec de la cr�ation d'instruction", sanitizer);
  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'assignement empil�e");
    
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
    debug_critical_exit("op�ration avec (au moins) un symbole invalide sur deux", sanitizer);
  
  debug_echoi("op�ration: $1 � l'adresse:", (int)arg1);
  debug_echoi("op�ration: $3 � l'adresse:", (int)arg3);

  //trouve le type de retour compatible avec ceux des arguments
  type_arg1 = ((CSymbol*)arg1)->getType();
  type_arg3 = ((CSymbol*)arg3)->getType();

  // Mes deux op�randes sont elles des pointeurs ?
  if( (type_arg1.getRef() > 0) && (type_arg3.getRef() > 0) )
  {
    // L'op�ration est elle autre chose qu'une soustraction OU/ET les op�randes
    // sont elles de type diff�rents ?
    if( (oprtr != OP3_SUB)
      || (type_arg1.getTypeVal() != type_arg3.getTypeVal()) ) 
      debug_critical_exit("Op�ration invalide sur un pointeur",sanitizer);
  }
  else
  {
    // R�sum� de l'�pisode : A ce point on sait que les op�randes ne sont
    // toutes les deux des pointeurs.

    // Il y a t'il une op�rande qui soit un pointeur ?
    // (on stocke laquelle des deux est le pointeur en question gr�ce �
    // a et b)
    if( (a=(type_arg1.getRef() > 0)) || (b=(type_arg3.getRef() > 0)) )
    {
      // L'op�ration est elle autre que l'addition ou la soustraction ?
      if( oprtr != OP3_ADD && oprtr != OP3_OR )
        debug_critical_exit("Op�ration invalide sur un pointeur",sanitizer);
      
      // Un petit hack ici pour exprimer de mani�re compacte :
      // L'op�rande qui n'est pas un pointeur est elle du type INT ?
      if( !( ( b && (type_arg1.getTypeVal() == T_INT))
          || ( a && (type_arg3.getTypeVal() == T_INT)) ) )
      {
      
        // L'op�ration est elle l'addition ?
        if( oprtr == OP3_ADD )
          debug_critical_exit("L'addition d'un pointeur est uniquement autoris�e\
avec un entier",sanitizer);
        else
          debug_critical_exit("La soustraction d'un pointeur est uniquement\
autoris�e avec un entier",sanitizer);

      }

    }

  }


  type_compatible = type_arg1.returnCompatible( type_arg3 ); 
  debug_echoi("Type de retour compatible trouv�:", type_compatible.getTypeVal());

  //cree le symbole de retour
  retval = CS_main->addSymbol( CStringID(), type_compatible ) ;
  debug_echoi("Symbole de retour pour l'op�ration cr�� � l'adresse:", (int)retval);
	
  //creation declaration pour le symbole de retour
  DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)type_compatible.getTypeVal() , DEFAULT_REF_LVL) ); 
  debug_echo("D�claration du symbole de retour empil�e");

  instr = new CInstruction( oprtr,
                            (CSymbol*) retval,
                            (CSymbol*) arg1,
                            (CSymbol*) arg3 
                          );

  if ( !instr->isValid() ) 
    debug_critical_exit("le constructeur d'instruction employ� ne correspond pas � l'op�rateur utilis�", sanitizer);
 
  //empilement
  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'op�ration valide et empil�e");
    
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
  // en cas d'arg1 ou arg3 non bool�ens
  CSymbol* arg1bool = NULL;
  CInstruction* arg1boolcast_instr = NULL;
  CSymbol* arg3bool = NULL;
  CInstruction* arg3boolcast_instr = NULL;

  if ( !(arg1) || !(arg3) )
    debug_critical_exit("op�ration avec (au moins) un symbole invalide sur deux", sanitizer);
  
  debug_echoi("op�ration: $1 � l'adresse:", (int)arg1);
  debug_echoi("op�ration: $3 � l'adresse:", (int)arg3);

  //gestion des types des arguments
  arg1_type_val = ((CSymbol*)arg1)->getType().getTypeVal();
  arg3_type_val = ((CSymbol*)arg3)->getType().getTypeVal();
 
  
  //gestion si symboles incompatibles
  if ( arg1_type_val != (TYPEVAL)T_BOOL ) {
    //some more code...   
    debug_echo("<cast de $1 en bool>");
    debug_echoi("$1 n'est pas de type BOOL, $1 est de type:", arg1_type_val);
    arg1bool = CS_main->addSymbol( CStringID(), CType( (TYPEVAL)T_BOOL, DEFAULT_REF_LVL) ) ; 
    debug_echoi("Symbole destin� � recevoir le cast en bool�en de $1 cr�� � l'adresse:",(int)arg1bool);
    DQ_main->addDeclaration( arg1bool->getID(), CType( (TYPEVAL)T_BOOL, DEFAULT_REF_LVL) ); 
    debug_echo("d�claration du symbole bool�en du cast de $1 empil�e");
    arg1boolcast_instr = new CInstruction ( (CSymbol*)arg1bool, (CSymbol*)arg1 );
    if ( !arg1boolcast_instr->isValid() ) 
    debug_critical_exit("le constructeur d'instruction du cast de $1 a �chou� ", sanitizer);
    IQ_main->pushInstruction( arg1boolcast_instr );
    debug_echo("instruction d'op�ration bool�enne sur $1 valide et empil�e");
    arg1 = (int)arg1bool;
    debug_echo("</cast de $1 en bool>");
 
  }
 
  if ( arg3_type_val != (TYPEVAL)T_BOOL ) {
    //some more code... 
    debug_echo("<cast de $3 en bool>"); 
    debug_echoi("$3 n'est pas de type BOOL, $3 est de type:", arg3_type_val);
    arg3bool = CS_main->addSymbol( CStringID(), CType( (TYPEVAL)T_BOOL, DEFAULT_REF_LVL) );
    debug_echoi("Symbole destin� � recevoir le cast en bool�en de $3 cr�� � l'adresse:",(int)arg3bool);   
    DQ_main->addDeclaration( arg3bool->getID(), CType( (TYPEVAL)T_BOOL, DEFAULT_REF_LVL) ); 
    debug_echo("d�claration du symbole bool�en du cast de $3 empil�e");
    arg3boolcast_instr = new CInstruction ( (CSymbol*)arg3bool, (CSymbol*)arg3 );
    if ( !arg3boolcast_instr->isValid() ) 
    debug_critical_exit("le constructeur d'instruction du cast de $3 a �chou� ", sanitizer);
    IQ_main->pushInstruction( arg3boolcast_instr );
    debug_echo("instruction d'op�ration bool�enne sur $3 valide et empil�e");
    arg3 = (int)arg3bool;  
    debug_echo("</cast de $3 en bool>");

  }
    
  //cree le symbole de retour de type bool
  retval = CS_main->addSymbol( CStringID(), CType( (TYPEVAL)T_BOOL, DEFAULT_REF_LVL) ) ;
  debug_echoi("symbole de retour pour l'op�ration bool�enne cr�� � l'adresse:", (int)retval);
	
  //creation declaration pour le symbole bool�en de retour
  DQ_main->addDeclaration( retval->getID(), CType( (TYPEVAL)T_BOOL, DEFAULT_REF_LVL) ); 
  debug_echo("d�claration du symbole bool�en de retour empil�e");

  instr = new CInstruction( oprtr,
                            (CSymbol*) retval,
                            (CSymbol*) arg1,
                            (CSymbol*) arg3 
                          );

  if ( !instr->isValid() ) 
    debug_critical_exit("le constructeur d'instruction employ� ne correspond pas � l'op�rateur bool�en utilis�", sanitizer);
 
  //empilement
  IQ_main->pushInstruction( instr );
  debug_echo("instruction d'op�ration bool�enne valide et empil�e");
    
  return ((int)retval);
}

int process_plus(int arg1, int arg3) {

  int pointeur = 0;
  debug_echo("<process plus>");
  pointeur = process_op3(arg1, arg3, OP3_ADD);
  if (!pointeur) debug_critical_exit("�chec de process_plus",sanitizer); 
  debug_echo("</process plus>");
  return pointeur;
    
}

int process_moins(int arg1, int arg3) {

  int pointeur = 0;
  debug_echo("<process moins>");
  pointeur = process_op3(arg1, arg3, OP3_SUB);
  if (!pointeur) debug_critical_exit("�chec de process_moins",sanitizer); 
  debug_echo("</process moins>");
  return pointeur;

}

int process_star(int arg1, int arg3) {

  int pointeur = 0;
  debug_echo("<process star>");
  pointeur = process_op3(arg1, arg3, OP3_MUL);
  if (!pointeur) debug_critical_exit("�chec de process_star",sanitizer); 
  debug_echo("</process star>");
  return pointeur;

}

int process_div(int arg1, int arg3) {

  int pointeur = 0;
  debug_echo("<process div>");
  pointeur = process_op3(arg1, arg3, OP3_DIV);
  if (!pointeur) debug_critical_exit("�chec de process_div",sanitizer); 
  debug_echo("</process div>");
  return pointeur;

}

 int process_bool_or(int arg1, int arg3) {
  
  int pointeur = 0;
  debug_echo("<process or>");
  pointeur = process_op3_bool(arg1, arg3, OP3_OR);
  if (!pointeur) debug_critical_exit("�chec de process_bool_or",sanitizer); 
  debug_echo("</process or>");
  return pointeur;

} 

int process_bool_and(int arg1, int arg3) {
 
  int pointeur = 0;
  debug_echo("<process and>");
  pointeur = process_op3_bool(arg1, arg3, OP3_AND);
  if (!pointeur) debug_critical_exit("�chec de process_bool_and",sanitizer); 
  debug_echo("</process and>");
  return pointeur;

}

int process_bool_eql(int arg1, int arg3) {
  
  int pointeur = 0;
  debug_echo("<process eql>");
  pointeur = process_op3_bool(arg1, arg3, OP3_EQL);
  if (!pointeur) debug_critical_exit("�chec de process_bool_eql",sanitizer); 
  debug_echo("</process eql>");
  return pointeur;

}

int process_grt(int arg1, int arg3) {
  
  int pointeur = 0;
  debug_echo("<process grt>");
  pointeur = process_op3(arg1, arg3, OP3_GRT);
  if (!pointeur) debug_critical_exit("�chec de process_bool_grt",sanitizer); 
  debug_echo("</process grt>");
  return pointeur;

}

int process_low(int arg1, int arg3) {
  
  int pointeur = 0;
  debug_echo("<process low>");
  pointeur = process_op3(arg1, arg3, OP3_LOW);
  if (!pointeur) debug_critical_exit("�chec de process_bool_low",sanitizer); 
  debug_echo("</process low>");
  return pointeur;

}

int process_bool_neq(int arg1, int arg3) {
  
  int pointeur = 0;
  debug_echo("<process neq>");
  pointeur = process_op3_bool(arg1, arg3, OP3_NEQ);
  if (!pointeur) debug_critical_exit("�chec de process_bool_neq",sanitizer); 
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
    debug_critical("impossible de d�r�f�rencer la variable");

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
      debug_critical("Pertes de donn�es lors du cast.");
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
