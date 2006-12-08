// vim: ts=2 tw=80

/** \file stringid.h
 * \brief Définit StringID valeur unique attribué à chaque
 *        chaine que le compilateur vera.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 07/12/2006
 *
 */

#ifndef STRINGID_H
#define STRINGID_H

#include "configuration.h"

class CStringID
{
public:
 
  CStringID()
  {
    hash = -1;
    depth = -1;
  }

  CStringID( int value )
  {
    this->fromInt(value);
  }

  CStringID( int hash, int depth )
  {
    this->hash = hash;
    this->depth = depth;
  }

 int toInt()
  {
    return ((this->depth)*HASHTABLE_SIZE + this->hash);
  }

  void fromInt(int value)
  {
    this->depth = value / HASHTABLE_SIZE;
    this->hash =  value % HASHTABLE_SIZE;
  }

  bool isValid()
  { 
    return ((hash != -1)&&(depth != -1)); 
  }

  bool operator == ( const CStringID& sid)
  {
    return ((hash == sid.hash)&&(depth == sid.depth));
  }

  int hash;
  int depth;
};

#endif/*STRINGID_H*/
