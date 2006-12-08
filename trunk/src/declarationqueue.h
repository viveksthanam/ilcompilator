//% vim: ts=2 tw=80

/** \file declarationstack.h
 * \brief Déclare la classe qui stocke les 
 * déclarations des variables.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#ifndef DECLARATIONSTACK_H
#define DECLARATIONSTACK_H

#include "configuration.h"
#include "symbol.h"
#include "type.h"


#include <stack>

using namespace std;

/**\brief Classe implémentant la pile des déclarations.
  *
  * En réalité cette classe n'implémente pas réellement une
  * pile mais du point de vue de l'utilisateur le résultat
  * est le même.
  */
class CDeclarationStack
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

  stack<DECLARATION> declarations;

public:

  /**\brief 
    */
  void addDeclaration( SymbolID id, CType type );

};

#endif/*DECLARATIONSTACK_H*/
