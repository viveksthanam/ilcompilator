#include <iostream>

#include "contextstack.h"

int main(void)
{
  CContextStack cs;

  cerr<<"Go !"<<endl;

  CSymbol* kikou;

  CType type;
  CStringID sid;
  
  int i;

  for(i=0;i<100;i++)
  {
    cerr<<"New CSymbol in stack"<<endl;
    
    kikou = new CSymbol( (SymbolID)i, sid, type);

    cs.pushSymbol( kikou ); 

    if( i == 50 )
    {
      cs.saveContext();
    }
  }

  cs.restoreContext();

  kikou = cs.getSymbol( (SymbolID)51 );

  if(!kikou)
    cerr<<"Got 51 -> NULL"<<endl;
  else
    cerr<<"Got 51 -> "<<(int)(kikou->getID())<<endl;

  kikou = cs.getSymbol( (SymbolID)50 );

  if(!kikou)
    cerr<<"Got 50 -> NULL"<<endl;
  else
    cerr<<"Got 50 -> "<<(int)(kikou->getID())<<endl;

  return 0;
}
