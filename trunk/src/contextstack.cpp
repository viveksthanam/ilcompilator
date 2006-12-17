// vim: ts=2 tw=80

/** \file contextstack.cpp
 * \brief Implémente la classe CContextStack qui contiendra
 * les différents symboles et ajoutera une information
 * sur le context dudit symbole.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version 
 * \date 07/12/2006
 *
 */

#include "contextstack.h"

CContextStack::CContextStack()
{
  // Initialise la numérotation des symboles.
  n = 0;

  size_stack.push(0);
}

CContextStack::~CContextStack()
{
  unsigned int i;

  for(i=0;i<symbols.size();i++)
  {
    delete (symbols[i]);
  }

  return;
}

CSymbol* CContextStack::addSymbol( CStringID sid, CType type )
{
  CSymbol* p_symbol = new CSymbol(this->n, sid, type);

  this->n++;

  /** \todo Ajouter une gestion d'erreur */
  if(!p_symbol) return NULL;
  
  pushSymbol( p_symbol );

  return p_symbol;
}

void CContextStack::pushSymbol( CSymbol* symbol )
{
  symbols.push_back(symbol);

  return;
}
 
CSymbol* CContextStack::getSymbolInContext( SymbolID id )
{
  int i;
  int min = 0;

  if( size_stack.size() > 0 )
    min = size_stack.top();

  for( i= symbols.size() - 1; i>=min; i-- )
  {
    if( (symbols[i])->getID() == id )
    {
      return (symbols[i]);
    }
  }

  return NULL;
}

CSymbol* CContextStack::getSymbolInContext( CStringID sid )
{
  int i;
  int min;
  
  if( size_stack.size() > 0 )
    min = size_stack.top();

  for( i= symbols.size() - 1; i>=min; i-- )
  {
    if( (symbols[i])->getSID() == sid )
    {
      return (symbols[i]);
    }
  }

  return NULL;
}

CSymbol* CContextStack::getSymbol( SymbolID id )
{
  int i;

  for( i = symbols.size() - 1; i>=0; i-- )
  {
    if( (symbols[i])->getID() == id )
    {
      return (symbols[i]);
    }
  }

  return NULL;
}

CSymbol* CContextStack::getSymbol( CStringID sid )
{
  int i;

  for( i= symbols.size() - 1; i>=0; i-- )
  {
    if( (symbols[i])->getSID() == sid )
    {
      return (symbols[i]);
    }
  }

  return NULL;
}


void CContextStack::saveContext(void)
{

  size_stack.push( symbols.size() );

  return;
}

void CContextStack::restoreContext(void)
{

  symbols.resize( size_stack.top() );

  size_stack.pop();

  return;
}
