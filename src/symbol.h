// vim: ts=2 tw=80

/** \file symbol.h
 * \brief Définit la classe CSymbol, contient les symboles
 *        utilisées dans le compilateur.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 07/12/2006
 *
 */

#ifndef SYMBOL_H
#define SYMBOL_H

#include "stringid.h"
#include "type.h"

typedef int SymbolID;

class CSymbol
{
private:

  SymbolID id;
  CStringID sid;
  CType type;

public:

  CSymbol( SymbolID id, CStringID sid, CType type )
  {
    this->id = id;
    this->sid = sid;
    this->type = type;
  }

  SymbolID getID() { return this->id; };
  CStringID getSID() { return this->sid; };
  CType getType() { return this->type; };

};

#endif/*SYMBOL_H*/
