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
  */

class CInstruction
{
private:

  /**\brief Bool�en indiquant que l'instruction est valide
    *et peut �tre empil� sur la file des instruction.*/
  bool isvalid;

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

  /**\brief Op�rande dans le cas du cast, � savoir le type
    * du cast.
    */
  CType cast_type;

  /**\brief Num�ro du label
    */
  int label;
  
  /**\brief Op�rande dans le cas de l'assignation simple
    * d'un constante � une variable
    */
 union
  { 
    bool bool_const_value;
    int int_const_value;
    float float_const_value;
  };

public:

  /**\brief Constructeur vide, place tous les membres dans 
    *un �tat invalide
    */
  CInstruction();

  /**\brief Constructeur de l'op�rateur label ou goto
    *\param n Num�ro du label.
    */
  CInstruction( Operator op, int n );

  /**\brief Constructeur de l'op�rateur de type if impliquant
    *un symbole (condition) et un num�ro de label.
    *\param n  Num�ro de label
    *\param ps CSymbol* pointant vers la condition de l'op�rateur.
    */
  CInstruction( Operator op, int n, CSymbol* ps );

 /**\brief Constructeur de l'instruction impliquant un op�rateur op
    *� 2 op�randes du type : lsymbol (op) rsymbol
    */
  CInstruction( Operator op, CSymbol* lsymbol, CSymbol* rsymbol);

  /**\brief Constructeur de l'instruction impliquant un op�rateur op
    *� 3 op�randes du type : lsymbol (op) rsymbol1 (op) rsymbol2
    */
  CInstruction( Operator op, CSymbol* lsymbol,
                CSymbol* rsymbol1, CSymbol* rsymbol2);

  /**\brief Constructeur de cast, renvoie l'instruction correcte
    * permettant de caster le symbole rsymbol en symbole lsymbol.
    * Si les deux symboles sont de m�me type alors l'op�rateur
    * sera un OP2_EQU.
    *\param lsymbol symbole de gauche.
    *\param rsymbol symbole de droite.
    */
  CInstruction(CSymbol* lsymbol, CSymbol* rsymbol);

  /**\brief Constructeur d'assignation d'une constante � une variable
    *\param lvalue symbole de gauche.
    *\param rvalue constante de droite
    */
  CInstruction(CSymbol* lvalue, float rvalue );

  /**\brief Constructeur DIY qui ne fait
    *qu'assigner les arguments aux membres.
    *\param op Op�rateur de l'instruction.
    *\param s1 SymbolID du premier argument.
    *\param s2 SymbolID du deuxieme argument.
    *\param s3 SymbolID du troisieme argument.
    *\param type CType d�crivant le type du cast si l'op�rateur
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

      this->isvalid=true;
  }

  /**\brief Accesseur
    *\return CInstruction::op
    */
  Operator getOperator() {return op;};

  /**\brief Accesseur
    *\return CInstruction::operand_1
    */
  SymbolID getOperand_1() {return operand_1; };

  /**\brief Accesseur
    *\return CInstruction::operand_2
    */
  SymbolID getOperand_2() {return operand_2; };

  /**\brief Accesseur
    *\return CInstruction::operand_3
    */
  SymbolID getOperand_3() {return operand_3; };

  /**\brief Accesseur
    *\return CInstruction::cast_type
    */
  CType getCastType() {return cast_type; };

  /**\brief Accesseur
    *\return CInstruction::bool_const_value
    */
  bool getBoolConstValue() {return bool_const_value; };

  /**\brief Accesseur
    *\return CInstruction::int_const_value
    */
  int getIntConstValue() {return int_const_value; };

  /**\brief Accesseur
    *\return CInstruction::float_const_value
    */
  float getFloatConstValue() {return float_const_value; };

  /**\brief Accesseur
    *\return CInstruction::isvalid
    */
  bool isValid() {return this->isvalid; };

  /**\brief Accesseur
    *\return CInstruction::label
    */
  int getLabel() {return this->label; };

};

#endif/*INSTRUCTION_H*/
