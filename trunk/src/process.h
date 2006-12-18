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

/** \brief G�n�re les d�clarations de variables du contexte. Alloue dynamiquement 
* un symbole et empile un pointeur vers celui-ci sur la CS courante.
* \param arg1 Type de symbole � d�clarer.
* \param arg2 TinyStringID identifiant le symbole.
* \param ref_level niveau de r�f�rencement du symbole.
* \return addSymbol() retourne un CSymbol*, mais ce n'est pas utile pour le moment,
* cela sert juste a tester s'il y a eu erreur d'allocation (NULL). 
*/
int process_declaration(int arg1, int arg2, int ref_level);

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
 * \todo Pr�voir le passage d'information au SymbolManager pour pointer les symboles
 * non r�utilisables dans le contexte courant.
 * \param val Entier remont� le Lex par yyval_int
 * \return CSymbol* pointeur sur symbole, pour rester coh�rent avec nos choix
 */
int process_int ( int val ); 

/** \brief Appel sur match d'un NUM_F. Proc�de � la d�claration d'un symbole, �
 * la production d'une instruction (affectation de val au symbole cr��) et
 * retourne le pointeur sur le symbole associ�.
 * \todo Pr�voir le passage d'information au SymbolManager pour pointer les symboles
 * non r�utilisables dans le contexte courant. 
 * \param val Entier remont� le Lex par yyval_float
 * \return CSymbol* pointeur sur symbole, pour rester coh�rent avec nos choix
 */
int process_float ( float val ); 

/** \brief Appel sur match d'un TRUE ou FALSE. Proc�de � la d�claration d'un symbole, �
 * la production d'une instruction (affectation de val au symbole cr��) et
 * retourne le pointeur sur le symbole associ�.
 * \todo Pr�voir le passage d'information au SymbolManager pour pointer les symboles
 * non r�utilisables dans le contexte courant. 
 * \param val Entier remont� le Lex (DEF_TRUE ou DEF_FALSE) 
 * \return CSymbol* pointeur sur symbole, pour rester coh�rent avec nos choix
 */
int process_bool ( int val ); 

/** \brief R�alise une assignation d'un symbole � un autre.
 * \param arg1 CSymbol* (cast� en int) cible.
 * \param arg3 CSymbol* (cast� en int) source.
 */
int process_assignment(int arg1, int arg3);


/** \brief R�alise une assignation d'une r�f�rence � un symbole.
 * \param arg1 CSymbol* (cast� en int) cible.
 * \param arg3 CSymbol* (cast� en int) source.
 */
int process_refassignment(int arg1, int arg3);


/** \brief Factorisation de code pour tous les traitements utilisant les
 * op�rateurs en OP3_*
 * \param arg1 CSymbol* cast� en int, premi�re op�rande de l'addition.
 * \param arg3 CSymbol* cast� en int, seconde op�rande de l'addition.
 * \param oprtr Op�rateur en OP3_* � utiliser lors du traitement.
 * \return CSymbol* a priori distinct des param�tres (sauf si le SymbolManager
 * est actif), pointant sur le symbole r�sultat. Ce Symbole de retour est
 * cast� implicitement si n�cessaire.
 * */
int process_op3(int arg1, int arg3, Operator oprtr);

/** \brief Factorisation de code pour tous les traitements utilisant les
 * op�rateurs bool�ens en OP3_*. Les arguments sont cast�s en bool si n�cessaire.
 * \param arg1 CSymbol* cast� en int, premi�re op�rande de l'addition.
 * \param arg3 CSymbol* cast� en int, seconde op�rande de l'addition.
 * \param oprtr Op�rateur en OP3_* � utiliser lors du traitement bool�en.
 * \return CSymbol* a priori distinct des param�tres (sauf si le SymbolManager
 * est actif), pointant sur le symbole bool�en r�sultat.  
 * */
int process_op3_bool(int arg1, int arg3, Operator oprtr);

/** \brief Proc�de � une addition et renvoie un pointeur sur le symbole
 * r�sultant de l'addition.
 * \param arg1 CSymbol* cast� en int, premi�re op�rande de l'addition.
 * \param arg3 CSymbol* cast� en int, seconde op�rande de l'addition.
 * \return CSymbol* a priori distinct des param�tres (sauf si le SymbolManager
 * est actif), pointant sur le symbole r�sultat de l'addition. Ce Symbol est
 * cast� implicitement si n�cessaire.
 */
int process_plus(int arg1, int arg3); 

/** \brief Idem soustraction.
 * \param arg1 CSymbol* cast� en int, premi�re op�rande.
 * \param arg3 CSymbol* cast� en int, seconde op�rande.
 * \return CSymbol* a priori distinct des param�tres (sauf si le SymbolManager
 * est actif), pointant sur le symbole r�sultat. Ce Symbol est
 * cast� implicitement si n�cessaire.
 */
int process_moins(int arg1, int arg3); 

/** \brief Idem multiplication.
 * \param arg1 CSymbol* cast� en int, premi�re op�rande.
 * \param arg3 CSymbol* cast� en int, seconde op�rande.
 * \return CSymbol* a priori distinct des param�tres (sauf si le SymbolManager
 * est actif), pointant sur le symbole r�sultat. Ce Symbol est
 * cast� implicitement si n�cessaire.
 */
int process_star(int arg1, int arg3); 

/** \brief Idem division.
 * \param arg1 CSymbol* cast� en int, premi�re op�rande.
 * \param arg3 CSymbol* cast� en int, seconde op�rande.
 * \return CSymbol* a priori distinct des param�tres (sauf si le SymbolManager
 * est actif), pointant sur le symbole r�sultat. Ce Symbol est
 * cast� implicitement si n�cessaire.
 */
int process_div(int arg1, int arg3); 

/** \brief Idem Sup�rieur 
 * \param arg1 CSymbol* cast� en int, premi�re op�rande.
 * \param arg3 CSymbol* cast� en int, seconde op�rande.
 * \return CSymbol* a priori distinct des param�tres (sauf si le SymbolManager
 * est actif), pointant sur le symbole bool�en r�sultat. Les arguments sont
 * cast�s si n�cessaire. 
 */
int process_grt(int arg1, int arg3); 

/** \brief Idem Inferieur
 * \param arg1 CSymbol* cast� en int, premi�re op�rande.
 * \param arg3 CSymbol* cast� en int, seconde op�rande.
 * \return CSymbol* a priori distinct des param�tres (sauf si le SymbolManager
 * est actif), pointant sur le symbole bool�en r�sultat. Les arguments sont
 * cast�s si n�cessaire. 
 */
int process_low(int arg1, int arg3); 

/** \brief Idem Est-Egal (bool�en)
 * \param arg1 CSymbol* cast� en int, premi�re op�rande.
 * \param arg3 CSymbol* cast� en int, seconde op�rande.
 * \return CSymbol* a priori distinct des param�tres (sauf si le SymbolManager
 * est actif), pointant sur le symbole bool�en r�sultat. Les arguments sont
 * cast�s si n�cessaire. 
 */
int process_bool_eql(int arg1, int arg3); 

/** \brief Idem Et (bool�en)
 * \param arg1 CSymbol* cast� en int, premi�re op�rande.
 * \param arg3 CSymbol* cast� en int, seconde op�rande.
 * \return CSymbol* a priori distinct des param�tres (sauf si le SymbolManager
 * est actif), pointant sur le symbole bool�en r�sultat. Les arguments sont
 * cast�s si n�cessaire. 
 */
int process_bool_and(int arg1, int arg3); 

/** \brief Idem Ou (bool�en)
 * \param arg1 CSymbol* cast� en int, premi�re op�rande.
 * \param arg3 CSymbol* cast� en int, seconde op�rande.
 * \return CSymbol* a priori distinct des param�tres (sauf si le SymbolManager
 * est actif), pointant sur le symbole bool�en r�sultat. Les arguments sont
 * cast�s si n�cessaire. 
 */
int process_bool_or(int arg1, int arg3); 

/** \brief Idem Est-Diff�rent (bool�en)
 * \param arg1 CSymbol* cast� en int, premi�re op�rande.
 * \param arg3 CSymbol* cast� en int, seconde op�rande.
 * \return CSymbol* a priori distinct des param�tres (sauf si le SymbolManager
 * est actif), pointant sur le symbole bool�en r�sultat. Les arguments sont
 * cast�s si n�cessaire. 
 */
int process_bool_neq(int arg1, int arg3); 

/** \brief R�alise les instructions n�cessaires � la cr�ation de la t�te
 *d'un bloc if...then ou if...then...else...
 * \param arg1 CSymbol* cast� en int, condition du bloc.
 */
int process_if(int arg1);

/** \brief R�alise les instructions n�cessaires � la cr�ation du bloc then
 *d'un bloc if...then ou if...then...else...
 */
int process_then();

/** \brief R�alise les instructions n�cessaires � la cr�ation du bloc else
 *d'un bloc if...then ou if...then...else...
 */
int process_else();

/** \brief R�alise les instructions n�cessaires � la cr�ation de la fin du bloc
 *d'un bloc if...then ou if...then...else...
 */
int process_fin_else();

/** \brief R�alise les instructions n�cessaires � la cr�ation de la fin du bloc
 *d'un while...do...
 *\param arg1 CSymbol* cast� en int de la variable condition
 *r�cup�r� de la fonction process
 */
int process_while_end(int arg1);

/** \brief R�alise les instructions n�cessaires � la cr�ation de la fin du bloc
 *d'un while...do...
 *\param arg4 CSymbol* cast� en int de la variable condition
 */
int process_repeat_end(int arg4);

/**\brief R�alise les instructions n�cessaires � la cr�ation du d�but du bloc
  *d'un repeat...until...
  */
int process_repeat_begin();

/**\brief R�alise les instructions n�cessaires � la cr�ation du d�but du bloc
  *d'un while...do...
  */
int process_while_begin();

/** \brief Fonction ne r�alisant rien si ce n'est $$ = $1
  * \param arg1 CSymbol* cast� en int
  * \return le symbol arg1 pass� en param�tre
  */
int process_exp_do_begin(int arg1);

/** \brief Fonction r�alisant l'op�ration de d�r�f�rencement
  * \param arg2 CSymbol* cast� en int argument de droite.
  * \return CSymbol* du symbol cr�e par l'op�ration.
  */
int process_uop_star(int arg2);

/** \brief Fonction r�alisant l'op�ration de cast.
  * \param arg1 TYPEVAL du type du cast.
  * \param arg4 CSymbol* cast� en int du symbole � caster.
  * \param ref_level Niveau de r�f�rencement du symbole.
  * \return CSymbol* cr�e par l'op�ration
  */
int process_uop_cast(int arg1, int arg4, int ref_level);

/** \brief Fonction r�alisant l'op�ration de n�gation logique
  * \param arg2 CSymbol* cast� en int argument de droite.
  * \return CSymbol* du symbole cr�e par l'op�ration.
  */
int process_uop_not(int arg2);

/** \brief Fonction r�alisant l'op�ration oppos�.
  * \param arg2 CSymbol* cast� en int argument de droite.
  * \return CSymbol* du symbole cr�e par l'op�ration.
  */
int process_uop_moins(int arg2);

/** @} */

#endif /*process.h*/

