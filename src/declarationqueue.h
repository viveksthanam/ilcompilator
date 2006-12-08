//% vim: ts=2 tw=80

/** \file declarationstack.h
 * \brief D�clare la classe qui stocke les 
 * d�clarations des variables.
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

/**\brief Classe impl�mentant la pile des d�clarations.
  *
  * En r�alit� cette classe n'impl�mente pas r�ellement une
  * pile mais du point de vue de l'utilisateur le r�sultat
  * est le m�me.
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
