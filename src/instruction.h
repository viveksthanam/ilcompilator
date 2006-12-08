//% vim: ts=2 tw=80

/** \file instruction.h
 * \brief D�finit la classe CInstruction charg�e de stocker
 * les informations sur une instruction 'code 3@'.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "operator.h"
#include "symbol.h"
#include "type.h"

/**\brief Classe d�crivant une instruction du code 3@.
  *
  */
class CInstruction
{
private:

  /**\brief Op�rateur utilis� lors dans l'instruction.*/
  Operator op;

  /**\brief Premi�re op�rande de l'op�rateur.
    *\note INVALID_SYMBOL si inutilis�.*/
  SymbolID operand_1;

  /**\brief Deuxi�me op�rande de l'op�rateur.
    *\note INVALID_SYMBOL si inutilis�.*/
  SymbolID operand_2;

  /**\brief Troisi�me op�rande de l'op�rateur.
    *\note INVALID_SYMBOL si inutilis�.*/
  SymbolID operand_3;

  /**\brief Troisi�me op�rande dans le cas du cast, � savoir le type
    * du cast.
    */
  CType cast_type;
  

public:

  /**\brief Constructeur vide, place toutes les membres dans 
    *un �tat invalide
    */
  CInstruction();

  /**\brief Constructeur de cast, renvoie l'instruction correcte
    * permettant de caster le symbole source en symbole target.
    *\param source type de base actuel.
    *\param target type de base souhait�.
    *\note Affiche un warning si une perte de donn�es r�sulte 
    * de l'op�ration.
    */
  CInstruction(CSymbol* source, CSymbol* target);

  Operator getOperator() {return op;};

  SymbolID getOperand_1() {return operand_1; };

  SymbolID getOperand_2() {return operand_2; };

  SymbolID getOperand_3() {return operand_3; };

  CType getCastType() {return cast_type; };
};

#endif/*INSTRUCTION_H*/
