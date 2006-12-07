// vim: ts=2 tw=80

/** \file hashtable.cpp
 * \brief Implémentation de la classe CHashtable, table de hachage
 *        permettant de fournir un StringID unique à une chaine et 
 *        d'y acceder ensuite avec une complexité faible.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version 
 * \date 07/12/2006
 *
 */

#include "hashtable.h"
#include "stringid.h"

CHashtable::CHashtable()
{
  return;
}

CHashtable::~CHashtable()
{

  return;
}

int CHashtable::getHashFromString( const char* str )
{
  int sum = 0;
  int i = 1;

  while( *str )
  {
    sum += i*(int)(*str);

    str++;
    i++;
  }

  sum %= HASHTABLE_SIZE;

  return sum;
}

string CHashtable::getStringFromStringID( CStringID sid )
{

  return string("");
}

CStringID CHashtable::getStringIDFromString( string str )
{
  int hash;
  int i;
  
  hash = getHashFromString( str.c_str() );
  
  for( i=0; i< str.size(); i++)
  {
    if( str == (lists[hash])[i] )
    {
    }
      
  }

  return CStringID();
}

