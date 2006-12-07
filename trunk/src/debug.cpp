/*fonctions de debug*/
using namespace std;
#include <iostream>
#include <cstdlib>
#include "debug.h"


// vim: ts=2 tw=80

/** \file debug.c
* \brief Corps des fonctions de debug
* \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
* \version
* \date 07/12/2007
*/

int debug_echo (char* string) {
#ifdef DEBUG_ECHO
 cerr << "debug_echo: " << string << endl;
#endif

  return EXIT_SUCCESS;
}

/*debug.c*/
