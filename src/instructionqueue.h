//% vim: ts=2 tw=80

/** \file instructionqueue.h
 * \brief Définit la classe CInstructionQueue chargée
 * de stocker les instructions code 3@.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#ifndef INSTRUCTIONQUEUE_H
#define INSTRUCTIONQUEUE_H

#include "configuration.h"

#include "instruction.h"

#include <queue>

using namespace std;

/**\brief Classe implémentant la pile des instructions.
  */
class CInstructionQueue
{
private:

  queue<CInstruction*> instructions;

public:

  ~CInstructionQueue();

  CInstruction* addInstruction();

  void pushInstruction( CInstruction* );

};

#endif/*INSTRUCTIONQUEUE_H*/
