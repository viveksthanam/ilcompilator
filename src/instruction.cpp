//% vim: ts=2 tw=80

/** \file instruction.cpp
 * \brief Définit la classe CInstruction chargée de stocker
 * les informations sur une instruction 'code 3@'.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#include "debug.h"
#include "instruction.h"

CInstruction::CInstruction()
{
  return;
}

CInstruction::CInstruction( CSymbol* source, CSymbol* target )
{

  if( !source->getType().canConvertTo( target->getType() ) )
  {
    debug_critical("Cast forcé: probable perte de données.");
  }
  
  return;
}

CInstruction::CInstruction( CSymbol* lvalue, float rvalue )
{

  switch(lvalue->getType().getTypeVal())
  {
    case T_BOOL:
      this->op = OP2_EQU_CONST_RVALUE_BOOL;
      this->bool_const_value = (rvalue != 0);
      break;

    case T_INT:
      this->op = OP2_EQU_CONST_RVALUE_INT;
      this->int_const_value = (int)rvalue;
      break;

    case T_FLOAT:
      this->op = OP2_EQU_CONST_RVALUE_FLOAT;
      this->float_const_value = rvalue;
      break;

    default:
      /**\todo Ajouter gestion d'erreur.*/
      break;
  }

  this->operand_1 = lvalue->getID();

  return;
}
