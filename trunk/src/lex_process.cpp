//% vim: ts=2 tw=80

/** \file lex_process.cpp 
 * \brief Corps des fonctions utilisées uniquement dans projet.l.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#include "hashtable.h"
#include "lex_process.h"
#include "stringid.h"
extern CHashtable HT_main;

/** \brief string correspond à yytext, ayant matché un ID. */ 
int lex_process_getTinyStringID( char* string ) {

	return HT_main.getStringIDFromString(string);	
	
}

