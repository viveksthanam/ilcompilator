/*fonctions de debug*/
using namespace std;
#include <iostream>
#include <cstdlib>
#define DEBUG_ECHO

int debug_echo (char* string) {
#ifdef DEBUG_ECHO
 cout << "debug_echo: " << string << endl;
#endif

  return EXIT_SUCCESS;
}

/*debug.c*/
