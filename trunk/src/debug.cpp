/*fonctions de debug*/
using namespace std;
#include <iostream>
#include <cstdlib>
#include "debug.h"
#include "configuration.h"
#include "hashtable.h"
#include "contextstack.h"

extern CHashtable* HT_main;
extern CContextStack* CS_main;
extern int debug_level;
extern int argc;
extern char** argv;

//% vim: ts=2 tw=80

/** \file debug.c
* \brief Corps des fonctions de debug
* \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
* \version
* \date 07/12/2007
*/

void about (void) {
  printf("ilCompilator - compil� le \
"__DATE__"\n<brossill@enseirb.fr><lerouxj@enseirb.fr>\n");
  return;
}

void debug_set_level (int* argc, char** argv) {

  if ( (*argc > 1) && ( strcmp(argv[DEBUG_FLAG_POSITION],DEBUG_FLAG) ) )
  debug_level = 1;	
  
  return;	 
}

void debug_critical_exit( char* str ) {
  
  cerr << "debug_critical_exit: " << str << endl;
  sanitizer();
  exit(EXIT_FAILURE);
  return; // inutile, mais bon tant pis ..

}

void debug_critical( char* str ) {

  cerr << "debug_critical: " << str << endl;
  return;

}

void sanitizer (void) {

delete CS_main;
delete HT_main;

}

int debug_echo (char* str) {
	
  if ( 1 == debug_level )
    cerr << "debug_echo: " << str << endl;

  return EXIT_SUCCESS;
}

int debug_echoi (char* str, int i) {

  if ( 1 == debug_level )
    cerr << "debug_echoi: " << str << ", parametre: " << i << endl;

  return EXIT_SUCCESS;
}

float debug_echof (char* str, float f) {

  if ( 1 == debug_level )
    cerr << "debug_echof: " << str << ", parametre: " << f << endl;

  return EXIT_SUCCESS;
}

int yyerror (char* str) {

  debug_critical( str );
  return EXIT_SUCCESS;	
}

/*debug.c*/
