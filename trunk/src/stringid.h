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

class CStringID
{
public:
 
  CStringID()
  {
    hash = -1;
    depth = -1;
  }

  CStringID( int hash, int depth )
  {
    this->hash = hash;
    this->depth = depth;
  }
  
  bool isValid() { return ((hash != -1)
                        &&(depth != -1)); }

  int hash;
  int depth;


};

#endif/*STRINGID_H*/
