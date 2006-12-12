//% vim: ts=2 tw=80

/** \file declarationqueue.h
 * \brief Déclare la classe qui stocke les 
 * déclarations des variables.
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

/**\brief Classe implémentant la file des déclarations.
  *
  * Au fur et à mesure que le compilateur lit le code source
  * il va empiler les instructions du code cible dans cette file.
  * Cette file sera par la suite vidée afin d'obtenir la liste 
  * des déclarations en tête de code 3@.
  */
class CDeclarationQueue
{
private:

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

  queue<DECLARATION> declarations;

public:

  /**\todo Documentation à faire. 
    */
  void addDeclaration( SymbolID id, CType type );


  bool empty() { return declarations.empty(); };

  DECLARATION* front() { return &(declarations.front()); };

  void pop() { declarations.pop(); };


};

#endif/*DECLARATIONQUEUE_H*/
