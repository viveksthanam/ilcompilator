//% vim: ts=2 tw=80

/** \file declarationstack.h
 * \brief Impl�mente la classe qui stocke les 
 * d�clarations des variables.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#include "declarationstack.h"

void CDeclarationStack::addDeclaration( SymbolID id, CType type )
{
  
  declarations.push( DECLARATION(id,type) );
  
  return;
}
