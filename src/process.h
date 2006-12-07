/* protos des fonctions de traitement */
#ifndef PROCESS_HEADER
#define PROCESS_HEADER

int process_declaration();
int process_assignment(int arg1, int arg3);
int process_while_end(int arg1, int arg2);
int process_repeat_end(int arg1, int arg4);
int process_while_begin();
int process_exp_do_begin(int arg1);
int process_repeat_begin();
int process_context_open();
int process_context_save();
int process_or(int arg1, int arg3); 
int process_and(int arg1, int arg3); 
int process_plus(int arg1, int arg3); 
int process_moins(int arg1, int arg3); 
int process_star(int arg1, int arg3); 
int process_div(int arg1, int arg3); 
int process_eql(int arg1, int arg3); 
int process_grt(int arg1, int arg3); 
int process_low(int arg1, int arg3); 
int process_neq(int arg1, int arg3); 
int process_uop(int arg1, int arg2); 

#endif /*process.h*/

