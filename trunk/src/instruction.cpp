//% vim: ts=2 tw=80

/** \file instruction.cpp
 * \brief D�finit la classe CInstruction charg�e de stocker
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
  this->isvalid = false;

  return;
}

CInstruction::CInstruction( CSymbol* lsymbol, CSymbol* rsymbol)
{

  if( rsymbol->getType() == lsymbol->getType() )
  {
    this->isvalid = true;

    this->op = OP2_EQU;
    this->operand_1 = lsymbol->getID();
    this->operand_2 = rsymbol->getID();

    return;
  }

  // Peut on convertir du rsymbol vers du lsymbol ?
  if( !rsymbol->getType().canConvertTo( lsymbol->getType() ) )
  {
    // On convertit de R vers L avec pertes 
    debug_critical("conversion implicite du symbole, avec perte de donn�es");
  }
 
  this->isvalid = true;

  this->op = OP3_CAST;
  this->operand_1 = lsymbol->getID();
  this->operand_2 = rsymbol->getID();
  this->cast_type = lsymbol->getType();

  return;
}

CInstruction::CInstruction( CSymbol* lvalue, float rvalue )
{

  switch(lvalue->getType().getTypeVal())
  {
    case T_BOOL:
      this->isvalid=true;
      this->op = OP2_EQU_CONST_RVALUE_BOOL;
      this->bool_const_value = (rvalue != 0);
      break;

    case T_INT:
      this->isvalid=true;
      this->op = OP2_EQU_CONST_RVALUE_INT;
      this->int_const_value = (int)rvalue;
      break;

    case T_FLOAT:
      this->isvalid=true;
      this->op = OP2_EQU_CONST_RVALUE_FLOAT;
      this->float_const_value = rvalue;
      break;

    default:
      this->isvalid=false;
      /**\todo Ajouter gestion d'erreur.*/
      break;
  }

  this->operand_1 = lvalue->getID();

  return;
}