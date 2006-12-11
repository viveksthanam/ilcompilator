/* protos des fonctions de traitement */
#ifndef PROCESS_HEADER
#define PROCESS_HEADER

// vim: ts=2 tw=80

/** \file process.h
* \brief Header des fonctions de traitement
* \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
* \version
* \date 07/12/2007
*/

/** \addtogroup ProcessingFunctions
* Appel lors d'un 'match' sur un token dans Yacc. Convention de nommage des
* fonctions: process_[nom du token].
* @{
*/

/** \brief Génère les déclarations de variables du contexte. Alloue dynamiquement 
* un symbole et empile un pointeur vers celui-ci sur la CS courante.
* \param int arg2 Correspond à l'id_aff.
* \return addSymbol() retourne un CSymbol*, mais ce n'est pas utile pour le moment,
* cela sert juste a tester s'il y a eu erreur d'allocation (NULL). 
*/
int process_declaration(int arg1, int arg2);

/** \brief Clôture une instruction de déclaration, repositionne 
* current_decl_type à -1.
*/
int process_declaration_end();

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

/** @} */

#endif /*process.h*/

