//% vim: ts=2 tw=80

/** \file lex_process.cpp 
 * \brief Corps des fonctions appelées dans projet.l.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#include <stdlib.h>

#include "hashtable.h"
#include "lex_process.h"
#include "stringid.h"
#include "debug.h"

int lex_process_getTinyStringID( CHashtable* my_HT, char* str ) {
	
	return (int)((CStringID)my_HT->getStringIDFromString(str)).toInt();	 

}

int lex_process_atoi ( char* str  ) {

  //paramètres 'par défaut' du strtol, idem ci-dessous pour strtof
	int i = (int)strtol(str,NULL,0);	
	debug_echoi("tentative de conversion strtoi sur NUM_I",i);
	return (i);

}

float lex_process_atof ( char* str ) {
		
	float f =  (float)strtof(str,NULL);
	debug_echof("tentative de conversion strtof sur NUM_F",f);
	return (f);

}
