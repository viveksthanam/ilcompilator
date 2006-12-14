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
  this->isvalid = false;

  return;
}

CInstruction::CInstruction( Operator op, int n )
{

  this->isvalid = true;

  this->op = op;

  this->label = n;

  return;
}

CInstruction::CInstruction( Operator op, int n, CSymbol* ps )
{

  this->isvalid = true;

  this->op = op;
  
  this->label = n;

  this->operand_1 = ps->getID();

  return;
}

CInstruction::CInstruction( Operator op, CSymbol* l,
                            CSymbol* r1, CSymbol* r2 )
{

  if( (op != OP3_ADD)
    &&(op != OP3_SUB)
    &&(op != OP3_MUL)
    &&(op != OP3_DIV)
    &&(op != OP3_AND)
    &&(op != OP3_OR)
    &&(op != OP3_EQL)
    &&(op != OP3_LOW)
    &&(op != OP3_SUP) )
  {
    this->isvalid = false;
  }

  this->op = op;

  this->operand_1 = l->getID();
  this->operand_2 = r1->getID();
  this->operand_3 = r2->getID();

  this->isvalid = true;

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
    debug_critical("conversion implicite du symbole, avec perte de données");
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
