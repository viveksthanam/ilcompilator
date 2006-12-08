/*fonctions de debug*/
using namespace std;
#include <iostream>
#include <cstdlib>
#include "debug.h"
#include "configuration.h"

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

void debug_set_level (int* argc, char** argv) {

  if ( (*argc > 1) && ( strcmp(argv[DEBUG_FLAG_POSITION],DEBUG_FLAG) ) )
  debug_level = 1;	
  
  return;	 
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

/*debug.c*/
