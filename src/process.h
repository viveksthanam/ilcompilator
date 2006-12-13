/* protos des fonctions de traitement */
#ifndef PROCESS_HEADER
#define PROCESS_HEADER

// vim: ts=2 tw=80

/** \brief Requis par process_id().
 */
#include "contextstack.h"

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
* \param arg1 Type de symbole à déclarer.
* \param arg2 TinyStringID identifiant le symbole.
* \return addSymbol() retourne un CSymbol*, mais ce n'est pas utile pour le moment,
* cela sert juste a tester s'il y a eu erreur d'allocation (NULL). 
*/
int process_declaration(int arg1, int arg2);
/** \brief Lorsque un ID est matché, process_id a deux comportements possibles: 
 * - soit on se trouve dans une zone de déclaration et on retourne simplement le
 *   TinyStringID passé en paramètre (et calculé dans Lex), afin de procéder à 
 *   la création du symbole plus haut dans l'arbre
 * - soit on se trouve dans une zone d'instruction et on recherche dans le
 *   contexte courant le Symbole (correspondant au TinyStringID passé en paramètre) 
 *   et on retourne un pointeur de type CSymbol* vers celui-ci, casté en int.
 *   \param current_CS Pointeur sur la ContextStack courante.
 *   \param tinystrid TinyStringID du symbole.
 */
int process_id ( int tinystrid, CContextStack* current_CS ); 

/** \brief Démarre une instruction de déclaration, positionne current_decl_type à type. 
 */
int process_type ( int type ); 

/** \brief Clôture une instruction de déclaration, repositionne 
* current_decl_type à -1.
*/
int process_declaration_end();

/** \brief Ouvre (empile) un nouveau contexte.
 * \return Pas de gestion d'erreur particulière, ceci est dû au prototype de la
 * méthode openContext.
 */
int process_context_open();

/** \brief Idem process_context_open, mais sauve (dépile).
 */
int process_context_save();

/** \brief Appel sur match d'un NUM_I. Procède à la déclaration d'un symbole, à
 * la production d'une instruction (affectation de val au symbole créé) et
 * retourne le pointeur sur le symbole associé.
 * \warning Pas de vérification de type pour le moment, donc le C réalise un
 * cast, qui (si la valeur a été corrompue depuis le strtoi ou strtol) peut
 * conduire à une perte d'information.
 * \todo Prévoir le passage d'information au SymbolManager pour pointer les symboles
 * non réutilisables dans le contexte courant.
 * \param val Entier remonté le Lex par yyval_int
 * \return CSymbol* pointeur sur symbole, pour rester cohérent avec nos choix
 */
int process_int ( int val ); 

/** \brief Appel sur match d'un NUM_F. Procède à la déclaration d'un symbole, à
 * la production d'une instruction (affectation de val au symbole créé) et
 * retourne le pointeur sur le symbole associé.
 * \warning Pas de vérification de type pour le moment, donc le C réalise un
 * cast, qui (si la valeur a été corrompue depuis le strtoi ou strtol) peut
 * conduire à une perte d'information.
 * \todo Prévoir le passage d'information au SymbolManager pour pointer les symboles
 * non réutilisables dans le contexte courant. 
 * \param val Entier remonté le Lex par yyval_float
 * \return CSymbol* pointeur sur symbole, pour rester cohérent avec nos choix
 */
int process_float ( float val ); 


/** \brief Appel sur match d'un TRUE ou FALSE. Procède à la déclaration d'un symbole, à
 * la production d'une instruction (affectation de val au symbole créé) et
 * retourne le pointeur sur le symbole associé.
 * \warning Pas de vérification de type pour le moment, donc le C réalise un
 * cast, qui (si la valeur a été corrompue depuis le strtoi ou strtol) peut
 * conduire à une perte d'information. 
 * \todo Prévoir le passage d'information au SymbolManager pour pointer les symboles
 * non réutilisables dans le contexte courant. 
 * \param val Entier remonté le Lex (DEF_TRUE ou DEF_FALSE) 
 * \return CSymbol* pointeur sur symbole, pour rester cohérent avec nos choix
 */
int process_bool ( int val ); 

/** \brief Réalise une assignation d'un symbole à un autre.
 * \param arg1 CSymbol* (casté en int) cible.
 * \param arg3 CSymbol* (casté en int) source.
 * \todo Implémenter la gestion de cast implicite si types source et cible
 * différents, le reste fonctionne.
 */
int process_assignment(int arg1, int arg3);

/** \brief Procède à une addition et renvoie un pointeur sur le symbole
 * résultant de l'addition.
 * \param arg1 CSymbol* casté en int, première opérande de l'addition.
 * \param arg2 CSymbol* casté en int, seconde opérande de l'addition.
 * \return CSymbol* a priori distinct des paramètres (sauf si le SymbolManager
 * est actif), pointant sur le symbole résultat de l'addition. Le CSymbol est
 * casté implicitement.
 */
int process_plus(int arg1, int arg3); 












/*a traiter:*/
int process_eql(int arg1, int arg3); 
int process_while_end(int arg1, int arg2);
int process_repeat_end(int arg1, int arg4);
int process_while_begin();
int process_exp_do_begin(int arg1);
int process_repeat_begin();
int process_or(int arg1, int arg3); 
int process_and(int arg1, int arg3); 
int process_moins(int arg1, int arg3); 
int process_star(int arg1, int arg3); 
int process_div(int arg1, int arg3); 
int process_grt(int arg1, int arg3); 
int process_low(int arg1, int arg3); 
int process_neq(int arg1, int arg3); 
int process_uop_star(int arg1, int arg2);
int process_uop_not(int arg1, int arg2);
int process_uop_moins(int arg1, int arg2);
/** @} */

#endif /*process.h*/

