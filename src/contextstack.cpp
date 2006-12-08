// vim: ts=2 tw=80

/** \file contextstack.cpp
 * \brief Implémente la classe CContextStack qui contiendra
 * les différents symboles et ajoutera une information
 * sur le context du dit symbole.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version 
 * \date 07/12/2006
 *
 */

#include "contextstack.h"

void CContextStack::pushSymbol( CSymbol* symbol )
{
  return;
}
 
CSymbol* CContextStack::getSymbolInContext( SymbolID )
{

  return NULL;
}

CSymbol* CContextStack::getSymbolInContext( CStringID )
{

  return NULL;
}

CSymbol* CContextStack::getSymbol( SymbolID )
{

  return NULL;
}

CSymbol* CContextStack::getSymbol( CStringID )
{

  return NULL;
}


void CContextStack::saveContext(void)
{
  return;
}

void CContextStack::restoreContext(void)
{
  return;
}
