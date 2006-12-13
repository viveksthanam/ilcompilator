//% vim: ts=2 tw=80

/** \file instruction.h
 * \brief Définit la classe CInstruction chargée de stocker
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

/**\brief Classe décrivant une instruction du code 3@.
  */

class CInstruction
{
private:

  /**\brief Opérateur utilisé lors dans l'instruction.*/
  Operator op;

  /**\brief Première opérande de l'opérateur.
    *\note INVALID_SYMBOL si inutilisé.*/
  SymbolID operand_1;

  /**\brief Deuxième opérande de l'opérateur.
    *\note INVALID_SYMBOL si inutilisé.*/
  SymbolID operand_2;

  /**\brief Troisième opérande de l'opérateur.
    *\note INVALID_SYMBOL si inutilisé.*/
  SymbolID operand_3;

  /**\brief Opérande dans le cas du cast, à savoir le type
    * du cast.
    */
  CType cast_type;
  
  /**\brief Opérande dans le cas de l'assignation simple
    * d'un constante à une variable
    */
  union
  { 
    bool bool_const_value;
    int int_const_value;
    float float_const_value;
  };

public:

  /**\brief Constructeur vide, place tous les membres dans 
    *un état invalide
    */
  CInstruction();

  /**\brief Constructeur de cast, renvoie l'instruction correcte
    * permettant de caster le symbole rsymbol en symbole lsymbol.
    * Si les deux symboles sont de même type alors l'opérateur
    * sera un OP2_EQU.
    *\param lsymbol symbole de gauche.
    *\param rsymbol symbole de droite.
    *\param warning met le booleen à vrai si un perte de données
    * résulte de l'opération.
    */
  CInstruction(CSymbol* lsymbol, CSymbol* rsymbol, bool& warning);

  /**\brief ...
    */
  CInstruction(CSymbol* lvalue, float rvalue );

  /**\brief Constructeur DIY qui ne fait
    *qu'assigner les arguments aux membres.
    *\param op Opérateur de l'instruction.
    *\param s1 SymbolID du premier argument.
    *\param s2 SymbolID du deuxieme argument.
    *\param s3 SymbolID du troisieme argument.
    *\param type CType décrivant le type du cast si l'opérateur
    *est un cast.
    */
  CInstruction( Operator op, SymbolID s1, SymbolID s2,
                SymbolID s3, CType type )
  {
      this->op = op;
      this->operand_1 = s1;
      this->operand_2 = s2;
      this->operand_3 = s3;
      this->cast_type = type;
  }

  Operator getOperator() {return op;};

  SymbolID getOperand_1() {return operand_1; };

  SymbolID getOperand_2() {return operand_2; };

  SymbolID getOperand_3() {return operand_3; };

  CType getCastType() {return cast_type; };

  bool getBoolConstValue() {return bool_const_value; };
  int getIntConstValue() {return int_const_value; };
  float getFloatConstValue() {return float_const_value; };
};

#endif/*INSTRUCTION_H*/
