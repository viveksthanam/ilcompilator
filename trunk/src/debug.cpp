//% vim: ts=2 tw=80

/** \file debug.cpp
* \brief Corps des fonctions de debug
* \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
* \version
* \date 07/12/2007
*/

using namespace std;

#include <iostream>
#include <cstdlib>

#include "debug.h"
#include "configuration.h"
#include "hashtable.h"
#include "contextstack.h"

int debug_level = 0;
extern int argc;
extern char** argv;

void about (void) {
  printf("ilCompilator - compilé le \
"__DATE__" à "__TIME__"\n<brossill@enseirb.fr><lerouxj@enseirb.fr>\n");
  return;
}

void debug_set_level (int* argc, char** argv) {

  if ( (*argc > 1) && ( strcmp(argv[DEBUG_FLAG_POSITION],DEBUG_FLAG) ) )
  debug_level = 1;	
  
  return;	 
}

void debug_critical( char* str ) {

  cerr << "debug_critical: " << str << endl;
  return;

}

void debug_critical_exit( char* str, void(*sanitizer)(void)  ) {
  
  cerr << "debug_critical_exit: " << str << endl;
  if(sanitizer) sanitizer();
  exit(EXIT_FAILURE);
  return; // inutile, mais bon tant pis ..
}


int debug_echo (char* str) {
	
  if ( 1 == debug_level )
    cerr << "debug_echo: " << str << endl;

  return EXIT_SUCCESS;
}

int debug_echoi (char* str, int i) {

  if ( 1 == debug_level )
    cerr << "debug_echoi: " << str << ", paramètre: " << i << endl;

  return EXIT_SUCCESS;
}

float debug_echof (char* str, float f) {

  if ( 1 == debug_level )
    cerr << "debug_echof: " << str << ", paramètre: " << f << endl;

  return EXIT_SUCCESS;
}

int yyerror (char* str) {

  debug_critical( str );
  return EXIT_SUCCESS;	
}

/*debug.c*/
