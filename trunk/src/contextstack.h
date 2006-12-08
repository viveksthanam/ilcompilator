// vim: ts=2 tw=80

/** \file context.h
 * \brief Définit la classe CContextStack qui contiendra
 * les différents symboles et ajoutera une information
 * sur le context du dit symbole.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 07/12/2006
 *
 */

#ifndef CONTEXTSTACK_H
#define CONTEXTSTACK_H

#include <vector>
#include <stack>

#include "symbol.h"

using namespace std;

class CContextStack
{
private:

  vector<CSymbol*> symbols;
  stack<int> size_stack;

public:

  CContextStack();
  ~CContextStack();

  void pushSymbol( CSymbol* );
  
  CSymbol* getSymbolInContext( SymbolID );
  CSymbol* getSymbolInContext( CStringID );

  CSymbol* getSymbol( SymbolID );
  CSymbol* getSymbol( CStringID );

  void saveContext(void);

  void restoreContext(void);
};

#endif/*CONTEXTSTACK_H*/
