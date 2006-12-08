/*fonctions de debug*/
using namespace std;
#include <iostream>
#include <cstdlib>
#include "debug.h"
#include "configuration.h"

extern int debug_level;

//% vim: ts=2 tw=80

/** \file debug.c
* \brief Corps des fonctions de debug
* \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
* \version
* \date 07/12/2007
*/

int debug_echo (char* string) {
	
  if ( 1 == debug_level )
    cerr << "debug_echo: " << string << endl;

  return EXIT_SUCCESS;
}

int debug_echoi (char* string, int i) {

  if ( 1 == debug_level )
    cerr << "debug_echoi: " << string << ", parametre: " << i << endl;

  return EXIT_SUCCESS;
}

/*debug.c*/
