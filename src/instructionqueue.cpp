//% vim: ts=2 tw=80

/** \file instructionstack.cpp
 * \brief Implémente la classe CInstructionStack chargée
 * de stocker les instructions code 3@.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#include "instructionqueue.h"

CInstructionQueue::~CInstructionQueue()
{

  while( !(instructions.empty()) )
  {
    delete (instructions.front());

    instructions.pop();
  }
  
  return;
}

CInstruction* CInstructionQueue::addInstruction( )
{

  return NULL;
}

void CInstructionQueue::pushInstruction( CInstruction* p_instr )
{

  instructions.push( p_instr );

  return;
}
