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

/** \brief G�n�re les d�clarations de variables du contexte. Alloue dynamiquement 
* un symbole et empile un pointeur vers celui-ci sur la CS courante.
* \param arg1 Type de symbole � d�clarer.
* \param arg2 TinyStringID identifiant le symbole.
* \return addSymbol() retourne un CSymbol*, mais ce n'est pas utile pour le moment,
* cela sert juste a tester s'il y a eu erreur d'allocation (NULL). 
*/
int process_declaration(int arg1, int arg2);
/** \brief Lorsque un ID est match�, process_id a deux comportements possibles: 
 * - soit on se trouve dans une zone de d�claration et on retourne simplement le
 *   TinyStringID pass� en param�tre (et calcul� dans Lex), afin de proc�der � 
 *   la cr�ation du symbole plus haut dans l'arbre
 * - soit on se trouve dans une zone d'instruction et on recherche dans le
 *   contexte courant le Symbole (correspondant au TinyStringID pass� en param�tre) 
 *   et on retourne un pointeur de type CSymbol* vers celui-ci, cast� en int.
 *   \param current_CS Pointeur sur la ContextStack courante.
 *   \param tinystrid TinyStringID du symbole.
 */
int process_id ( int tinystrid, CContextStack* current_CS ); 

/** \brief D�marre une instruction de d�claration, positionne current_decl_type � type. 
 */
int process_type ( int type ); 

/** \brief Cl�ture une instruction de d�claration, repositionne 
* current_decl_type � -1.
*/
int process_declaration_end();

/** \brief Ouvre (empile) un nouveau contexte.
 * \return Pas de gestion d'erreur particuli�re, ceci est d� au prototype de la
 * m�thode openContext.
 */
int process_context_open();

/** \brief Idem process_context_open, mais sauve (d�pile).
 */
int process_context_save();

/** \brief Appel sur match d'un NUM_I. Proc�de � la d�claration d'un symbole, �
 * la production d'une instruction (affectation de val au symbole cr��) et
 * retourne le pointeur sur le symbole associ�.
 * \warning Pas de v�rification de type pour le moment, donc le C r�alise un
 * cast, qui (si la valeur a �t� corrompue depuis le strtoi ou strtol) peut
 * conduire � une perte d'information.
 * \todo Pr�voir le passage d'information au SymbolManager pour pointer les symboles
 * non r�utilisables dans le contexte courant.
 * \param val Entier remont� le Lex par yyval_int
 * \return CSymbol* pointeur sur symbole, pour rester coh�rent avec nos choix
 */
int process_int ( int val ); 

/** \brief Appel sur match d'un NUM_F. Proc�de � la d�claration d'un symbole, �
 * la production d'une instruction (affectation de val au symbole cr��) et
 * retourne le pointeur sur le symbole associ�.
 * \warning Pas de v�rification de type pour le moment, donc le C r�alise un
 * cast, qui (si la valeur a �t� corrompue depuis le strtoi ou strtol) peut
 * conduire � une perte d'information.
 * \todo Pr�voir le passage d'information au SymbolManager pour pointer les symboles
 * non r�utilisables dans le contexte courant. 
 * \param val Entier remont� le Lex par yyval_float
 * \return CSymbol* pointeur sur symbole, pour rester coh�rent avec nos choix
 */
int process_float ( float val ); 


/** \brief Appel sur match d'un TRUE ou FALSE. Proc�de � la d�claration d'un symbole, �
 * la production d'une instruction (affectation de val au symbole cr��) et
 * retourne le pointeur sur le symbole associ�.
 * \warning Pas de v�rification de type pour le moment, donc le C r�alise un
 * cast, qui (si la valeur a �t� corrompue depuis le strtoi ou strtol) peut
 * conduire � une perte d'information. 
 * \todo Pr�voir le passage d'information au SymbolManager pour pointer les symboles
 * non r�utilisables dans le contexte courant. 
 * \param val Entier remont� le Lex (DEF_TRUE ou DEF_FALSE) 
 * \return CSymbol* pointeur sur symbole, pour rester coh�rent avec nos choix
 */
int process_bool ( int val ); 

/** \brief R�alise une assignation d'un symbole � un autre.
 * \param arg1 CSymbol* (cast� en int) cible.
 * \param arg3 CSymbol* (cast� en int) source.
 * \todo Impl�menter la gestion de cast implicite si types source et cible
 * diff�rents, le reste fonctionne.
 */
int process_assignment(int arg1, int arg3);

/** \brief Proc�de � une addition et renvoie un pointeur sur le symbole
 * r�sultant de l'addition.
 * \param arg1 CSymbol* cast� en int, premi�re op�rande de l'addition.
 * \param arg2 CSymbol* cast� en int, seconde op�rande de l'addition.
 * \return CSymbol* a priori distinct des param�tres (sauf si le SymbolManager
 * est actif), pointant sur le symbole r�sultat de l'addition. Le CSymbol est
 * cast� implicitement.
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

