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

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "stringid.h"

#include <string>
#include <queue>

#define HASHTABLE_SIZE 100

using namespace std;

class CHashtable
{
private:

  vector<string> table[HASHTABLE_SIZE];
  
  int getHashFromString( const char* );

public:

  CHashtable();
  ~CHashtable();

  string getStringFromStringID( CStringID );
  
  CStringID getStringIDFromString( string );
  
};

#endif/*HASHTABLE_H*/
