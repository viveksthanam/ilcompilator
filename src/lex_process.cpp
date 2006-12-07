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

/** \todo Regler le probleme de fuite memoire (du a getstringidfrom string ?) !
 * */ 
int lex_process_getTinyStringID( CHashtable* my_HT, char* string ) {

	return (int)((CStringID)my_HT->getStringIDFromString(string)).toInt();	

}

