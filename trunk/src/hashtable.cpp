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

#include <iostream>

CHashtable::CHashtable()
{
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
  if( !(sid.isValid()) ) return string("ERROR");
  
  return (table[sid.hash])[sid.depth];
}

CStringID CHashtable::getStringIDFromString( string str )
{
  int hash;
  unsigned int i;
  
  hash = getHashFromString( str.c_str() );
  
  // Cherche dans la table à l'indice 'hash'
  // en dépilant la liste jusqu'a tomber
  // sur la chaine qui nous interesse.
  // Si on tombe pas dessus alors on va la créer.
  for( i=0; i<(table[hash]).size(); i++)
  {
    if( str == (table[hash])[i] )
      return CStringID( hash, i );
  }

  // Création de l'entrée dans la table de hash.
  //  table[hash].insert( table[hash].begin(), str );
  table[hash].push_back( str );

  // Retourne le CStringID "qui va bien"(c)
  return CStringID( hash, table[hash].size() - 1);
}

