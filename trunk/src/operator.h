//% vim: ts=2 tw=80

/** \file operator.h
 * \brief Définit le type Operator énumérant les différents
 * types d'opérateurs du langage 3@.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#ifndef OPERATOR_H
#define OPERATOR_H

/**\brief Operator est un typdef enum listant les opérateurs du
  * langage 3@.
  *
  * \note Un opérateur est la pluspart du temps un ensemble de 
  * 2 opérateurs en effet OP3_ADD décrit l'opération : A=B+C.
  * Dans OPx_<operateur> x détermine le nombre d'opérandes utilisés
  * par l'opérateur. Il ne s'agit en aucun d'une notation active
  * mais d'une norme d'écriture.
  * \warning L'opérateur OP3_CAST prend en réalité 3 paramètres :
  * la variable de gauche, celle de droite et le type vers lequel
  * le cast est effectué.
  */
typedef enum _Operator
{
  OP3_ADD = 0,
  OP3_SUB,
  OP3_MUL,
  OP3_DIV,

  OP3_AND,
  OP3_OR,

  OP3_EQL,
  OP3_LOW,
  OP3_SUP,
  
  OP2_EQU,
  OP2_EQU_CONST_RVALUE_BOOL,
  OP2_EQU_CONST_RVALUE_INT,
  OP2_EQU_CONST_RVALUE_FLOAT,
  
  OP3_CAST,

  OP1_LABEL,
  OP1_GOTO,
  OP2_IF,

  OP0_INVALID //Définit l'opérateur invalide et est utilisé
              //  pour mesurer la taille de l'énum.

}Operator;

#endif/*OPERATOR_H*/
