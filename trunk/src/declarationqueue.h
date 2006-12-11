//% vim: ts=2 tw=80

/** \file declarationqueue.h
 * \brief D�clare la classe qui stocke les 
 * d�clarations des variables.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#ifndef DECLARATIONQUEUE_H
#define DECLARATIONQUEUE_H

#include "configuration.h"
#include "symbol.h"
#include "type.h"


#include <queue>

using namespace std;

/**\brief Classe impl�mentant la file des d�clarations.
  *
  * Au fur et a mesure que le compilateur lit le code source
  * il va empiler les instructions du code cible dans cette file.
  * Cette file sera par la suite vid�e afin
  */
class CDeclarationQueue
{
public:
  typedef struct _DECLARATION
  {

    _DECLARATION(SymbolID id, CType type)
    {
      this->id = id;
      this->type = type;
    }

    SymbolID id;
    CType type;

  }DECLARATION;

private:

  queue<DECLARATION> declarations;

public:

  /**\brief Ajoute une d�claration dans la file.
    */
  void addDeclaration( SymbolID id, CType type );

  bool empty() { return declarations.empty(); };

  DECLARATION* front() { return &(declarations.front()); };

  void pop() { declarations.pop(); };

};

#endif/*DECLARATIONQUEUE_H*/
