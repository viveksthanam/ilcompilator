//% vim: ts=2 tw=80

/** \file lex_process.cpp 
 * \brief Corps des fonctions utilisées uniquement dans projet.l.
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

	int i = (int)strtol(str,NULL,0);	
	debug_echoi("lex_process_atoi sur NUM_I",i);
	return (i);

}

float lex_process_atof ( char* str ) {
		
	float f =  (float)strtof(str,NULL);
	debug_echof("lex_process_atof sur NUM_F",f);
	return (f);

}
