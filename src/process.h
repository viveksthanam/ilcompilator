// vim: ts=2 tw=80

/** \file process.h
* \brief Header des fonctions de traitement
* \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
* \version
* \date 07/12/2007
*/

#ifndef PROCESS_HEADER
#define PROCESS_HEADER

#include "operator.h"
#include "contextstack.h"

/** \addtogroup ProcessingFunctions
* Appel lors d'un 'match' sur un token dans Yacc.
* @{
*/

/** \brief Génère les déclarations de variables du contexte. Alloue dynamiquement 
* un symbole et empile un pointeur vers celui-ci sur la CS courante.
* \param arg1 Type de symbole à déclarer.
* \param arg2 TinyStringID identifiant le symbole.
* \param ref_level niveau de référencement du symbole.
* \return addSymbol() retourne un CSymbol*, mais ce n'est pas utile pour le moment,
* cela sert juste a tester s'il y a eu erreur d'allocation (NULL). 
*/
int process_declaration(int arg1, int arg2, int ref_level);

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
 * \todo Prévoir le passage d'information au SymbolManager pour pointer les symboles
 * non réutilisables dans le contexte courant.
 * \param val Entier remonté le Lex par yyval_int
 * \return CSymbol* pointeur sur symbole, pour rester cohérent avec nos choix
 */
int process_int ( int val ); 

/** \brief Appel sur match d'un NUM_F. Procède à la déclaration d'un symbole, à
 * la production d'une instruction (affectation de val au symbole créé) et
 * retourne le pointeur sur le symbole associé.
 * \todo Prévoir le passage d'information au SymbolManager pour pointer les symboles
 * non réutilisables dans le contexte courant. 
 * \param val Entier remonté le Lex par yyval_float
 * \return CSymbol* pointeur sur symbole, pour rester cohérent avec nos choix
 */
int process_float ( float val ); 

/** \brief Appel sur match d'un TRUE ou FALSE. Procède à la déclaration d'un symbole, à
 * la production d'une instruction (affectation de val au symbole créé) et
 * retourne le pointeur sur le symbole associé.
 * \todo Prévoir le passage d'information au SymbolManager pour pointer les symboles
 * non réutilisables dans le contexte courant. 
 * \param val Entier remonté le Lex (DEF_TRUE ou DEF_FALSE) 
 * \return CSymbol* pointeur sur symbole, pour rester cohérent avec nos choix
 */
int process_bool ( int val ); 

/** \brief Réalise une assignation d'un symbole à un autre.
 * \param arg1 CSymbol* (casté en int) cible.
 * \param arg3 CSymbol* (casté en int) source.
 */
int process_assignment(int arg1, int arg3);


/** \brief Réalise une assignation d'une référence à un symbole.
 * \param arg1 CSymbol* (casté en int) cible.
 * \param arg3 CSymbol* (casté en int) source.
 */
int process_refassignment(int arg1, int arg3);


/** \brief Factorisation de code pour tous les traitements utilisant les
 * opérateurs en OP3_*
 * \param arg1 CSymbol* casté en int, première opérande de l'addition.
 * \param arg3 CSymbol* casté en int, seconde opérande de l'addition.
 * \param oprtr Opérateur en OP3_* à utiliser lors du traitement.
 * \return CSymbol* a priori distinct des paramètres (sauf si le SymbolManager
 * est actif), pointant sur le symbole résultat. Ce Symbole de retour est
 * casté implicitement si nécessaire.
 * */
int process_op3(int arg1, int arg3, Operator oprtr);

/** \brief Factorisation de code pour tous les traitements utilisant les
 * opérateurs booléens en OP3_*. Les arguments sont castés en bool si nécessaire.
 * \param arg1 CSymbol* casté en int, première opérande de l'addition.
 * \param arg3 CSymbol* casté en int, seconde opérande de l'addition.
 * \param oprtr Opérateur en OP3_* à utiliser lors du traitement booléen.
 * \return CSymbol* a priori distinct des paramètres (sauf si le SymbolManager
 * est actif), pointant sur le symbole booléen résultat.  
 * */
int process_op3_bool(int arg1, int arg3, Operator oprtr);

/** \brief Procède à une addition et renvoie un pointeur sur le symbole
 * résultant de l'addition.
 * \param arg1 CSymbol* casté en int, première opérande de l'addition.
 * \param arg3 CSymbol* casté en int, seconde opérande de l'addition.
 * \return CSymbol* a priori distinct des paramètres (sauf si le SymbolManager
 * est actif), pointant sur le symbole résultat de l'addition. Ce Symbol est
 * casté implicitement si nécessaire.
 */
int process_plus(int arg1, int arg3); 

/** \brief Idem soustraction.
 * \param arg1 CSymbol* casté en int, première opérande.
 * \param arg3 CSymbol* casté en int, seconde opérande.
 * \return CSymbol* a priori distinct des paramètres (sauf si le SymbolManager
 * est actif), pointant sur le symbole résultat. Ce Symbol est
 * casté implicitement si nécessaire.
 */
int process_moins(int arg1, int arg3); 

/** \brief Idem multiplication.
 * \param arg1 CSymbol* casté en int, première opérande.
 * \param arg3 CSymbol* casté en int, seconde opérande.
 * \return CSymbol* a priori distinct des paramètres (sauf si le SymbolManager
 * est actif), pointant sur le symbole résultat. Ce Symbol est
 * casté implicitement si nécessaire.
 */
int process_star(int arg1, int arg3); 

/** \brief Idem division.
 * \param arg1 CSymbol* casté en int, première opérande.
 * \param arg3 CSymbol* casté en int, seconde opérande.
 * \return CSymbol* a priori distinct des paramètres (sauf si le SymbolManager
 * est actif), pointant sur le symbole résultat. Ce Symbol est
 * casté implicitement si nécessaire.
 */
int process_div(int arg1, int arg3); 

/** \brief Idem Supérieur 
 * \param arg1 CSymbol* casté en int, première opérande.
 * \param arg3 CSymbol* casté en int, seconde opérande.
 * \return CSymbol* a priori distinct des paramètres (sauf si le SymbolManager
 * est actif), pointant sur le symbole booléen résultat. Les arguments sont
 * castés si nécessaire. 
 */
int process_grt(int arg1, int arg3); 

/** \brief Idem Inferieur
 * \param arg1 CSymbol* casté en int, première opérande.
 * \param arg3 CSymbol* casté en int, seconde opérande.
 * \return CSymbol* a priori distinct des paramètres (sauf si le SymbolManager
 * est actif), pointant sur le symbole booléen résultat. Les arguments sont
 * castés si nécessaire. 
 */
int process_low(int arg1, int arg3); 

/** \brief Idem Est-Egal (booléen)
 * \param arg1 CSymbol* casté en int, première opérande.
 * \param arg3 CSymbol* casté en int, seconde opérande.
 * \return CSymbol* a priori distinct des paramètres (sauf si le SymbolManager
 * est actif), pointant sur le symbole booléen résultat. Les arguments sont
 * castés si nécessaire. 
 */
int process_bool_eql(int arg1, int arg3); 

/** \brief Idem Et (booléen)
 * \param arg1 CSymbol* casté en int, première opérande.
 * \param arg3 CSymbol* casté en int, seconde opérande.
 * \return CSymbol* a priori distinct des paramètres (sauf si le SymbolManager
 * est actif), pointant sur le symbole booléen résultat. Les arguments sont
 * castés si nécessaire. 
 */
int process_bool_and(int arg1, int arg3); 

/** \brief Idem Ou (booléen)
 * \param arg1 CSymbol* casté en int, première opérande.
 * \param arg3 CSymbol* casté en int, seconde opérande.
 * \return CSymbol* a priori distinct des paramètres (sauf si le SymbolManager
 * est actif), pointant sur le symbole booléen résultat. Les arguments sont
 * castés si nécessaire. 
 */
int process_bool_or(int arg1, int arg3); 

/** \brief Idem Est-Différent (booléen)
 * \param arg1 CSymbol* casté en int, première opérande.
 * \param arg3 CSymbol* casté en int, seconde opérande.
 * \return CSymbol* a priori distinct des paramètres (sauf si le SymbolManager
 * est actif), pointant sur le symbole booléen résultat. Les arguments sont
 * castés si nécessaire. 
 */
int process_bool_neq(int arg1, int arg3); 

/** \brief Réalise les instructions nécessaires à la création de la tête
 *d'un bloc if...then ou if...then...else...
 * \param arg1 CSymbol* casté en int, condition du bloc.
 */
int process_if(int arg1);

/** \brief Réalise les instructions nécessaires à la création du bloc then
 *d'un bloc if...then ou if...then...else...
 */
int process_then();

/** \brief Réalise les instructions nécessaires à la création du bloc else
 *d'un bloc if...then ou if...then...else...
 */
int process_else();

/** \brief Réalise les instructions nécessaires à la création de la fin du bloc
 *d'un bloc if...then ou if...then...else...
 */
int process_fin_else();

/** \brief Réalise les instructions nécessaires à la création de la fin du bloc
 *d'un while...do...
 *\param arg1 CSymbol* casté en int de la variable condition
 *récupéré de la fonction process
 */
int process_while_end(int arg1);

/** \brief Réalise les instructions nécessaires à la création de la fin du bloc
 *d'un while...do...
 *\param arg4 CSymbol* casté en int de la variable condition
 */
int process_repeat_end(int arg4);

/**\brief Réalise les instructions nécessaires à la création du début du bloc
  *d'un repeat...until...
  */
int process_repeat_begin();

/**\brief Réalise les instructions nécessaires à la création du début du bloc
  *d'un while...do...
  */
int process_while_begin();

/** \brief Fonction ne réalisant rien si ce n'est $$ = $1
  * \param arg1 CSymbol* casté en int
  * \return le symbol arg1 passé en paramètre
  */
int process_exp_do_begin(int arg1);

/** \brief Fonction réalisant l'opération de déréférencement
  * \param arg2 CSymbol* casté en int argument de droite.
  * \return CSymbol* du symbol crée par l'opération.
  */
int process_uop_star(int arg2);

/** \brief Fonction réalisant l'opération de cast.
  * \param arg1 TYPEVAL du type du cast.
  * \param arg4 CSymbol* casté en int du symbole à caster.
  * \param ref_level Niveau de référencement du symbole.
  * \return CSymbol* crée par l'opération
  */
int process_uop_cast(int arg1, int arg4, int ref_level);

/** \brief Fonction réalisant l'opération de négation logique
  * \param arg2 CSymbol* casté en int argument de droite.
  * \return CSymbol* du symbole crée par l'opération.
  */
int process_uop_not(int arg2);

/** \brief Fonction réalisant l'opération opposé.
  * \param arg2 CSymbol* casté en int argument de droite.
  * \return CSymbol* du symbole crée par l'opération.
  */
int process_uop_moins(int arg2);

/** @} */

#endif /*process.h*/

