/*code des routines de traitement*/
using namespace std;
#include <iostream>
#include <cstdlib>
#include "process.hpp"

int process_declaration() {

  cout << "declaration: type id_aff_list PV\n ";
 
  /* la production de code "quasiment online" peut commencer :P */
  
  return EXIT_SUCCESS;
}

int process_assignment(int arg1, int arg3) {

  cout << "assignment: id EQ exp\n";
  return EXIT_SUCCESS;
}

int process_while_end(int arg1, int arg2) {

  cout << "while_end: while exp_do inst\n";
  return EXIT_SUCCESS;
}

int process_repeat_end(int arg1, int arg4) {

  cout << "repeat_end: repeat inst UNTIL exp\n";
  return EXIT_SUCCESS;
}

int process_while_begin() {

  cout << "while_begin: WHILE\n";
  return EXIT_SUCCESS;
}

int process_exp_do_begin(int arg1) {

  cout << "exp_do_begin: exp DO\n";
  return EXIT_SUCCESS;
}

int process_repeat_begin() {

  cout << "repeat_begin: REPEAT\n";
  return EXIT_SUCCESS;
}

int process_context_open() {

  cout << "context_open: DA\n";
  return EXIT_SUCCESS;
}

int process_context_save() {

  cout << "context_save: FA\n";
  return EXIT_SUCCESS;
}

int process_or(int arg1, int arg3) {

  cout << "or: exp OR exp\n";
  return EXIT_SUCCESS;
} 

int process_and(int arg1, int arg3) {

  cout << "and: exp AND exp\n";
  return EXIT_SUCCESS;
}

int process_plus(int arg1, int arg3) {

  cout << "plus: exp PLUS exp\n";
  return EXIT_SUCCESS;
}

int process_moins(int arg1, int arg3) {

  cout << "moins: exp MOINS exp\n";
  return EXIT_SUCCESS;
}

int process_star(int arg1, int arg3) {

  cout << "star: exp STAR exp\n";
  return EXIT_SUCCESS;
}

int process_div(int arg1, int arg3) {

  cout << "div: exp DIV exp\n";
  return EXIT_SUCCESS;
}

int process_eql(int arg1, int arg3) {

  cout << "eql: exp EQL exp\n";
  return EXIT_SUCCESS;
}

int process_grt(int arg1, int arg3) {

  cout << "grt: exp GRT exp\n";
  return EXIT_SUCCESS;
}

int process_low(int arg1, int arg3) {

  cout << "low: exp LOW exp\n";
  return EXIT_SUCCESS;
}

int process_neq(int arg1, int arg3) {

  cout << "neq: exp NEQ exp\n";
  return EXIT_SUCCESS;
}
 
int process_uop(int arg1, int arg2) {

  cout << "uop: uop exp %prec MUNAIRE\n";
  return EXIT_SUCCESS;
}

/* fin process.cpp */
