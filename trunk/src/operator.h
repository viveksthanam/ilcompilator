//% vim: ts=2 tw=80

/** \file operator.h
 * \brief D�finit le type Operator �num�rant les diff�rents
 * types d'op�rateurs du langage 3@.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#ifndef OPERATOR_H
#define OPERATOR_H

/**\brief Operator est un typdef enum listant les op�rateurs du
  * langage 3@.
  *
  * \note Un op�rateur est la pluspart du temps un ensemble de 
  * 2 op�rateurs en effet OP3_ADD d�crit l'op�ration : A=B+C.
  * Dans OPx_<operateur> x d�termine le nombre d'op�randes utilis�s
  * par l'op�rateur. Il ne s'agit en aucun d'une notation active
  * mais d'une norme d'�criture.
  * \warning L'op�rateur OP3_CAST prend en r�alit� 3 param�tres :
  * la variable de gauche, celle de droite et le type vers lequel
  * le cast est effectu�.
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

  OP0_INVALID //D�finit l'op�rateur invalide et est utilis�
              //  pour mesurer la taille de l'�num.

}Operator;

#endif/*OPERATOR_H*/
