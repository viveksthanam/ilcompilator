//% vim: ts=2 tw=80

/** \file declarationqueue.h
 * \brief Implémente la classe qui stocke les 
 * déclarations des variables.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#include "declarationqueue.h"

void CDeclarationQueue::addDeclaration( SymbolID id, CType type )
{
  
  declarations.push( DECLARATION(id,type) );
  
  return;
}
