// vim: ts=2 tw=80

/** \file 
 * \brief 
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 
 *
 */

#ifndef TYPE_H
#define TYPE_H

typedef enum _TYPEVAL
{
  T_BOOL = 0,
  T_INT,
  T_FLOAT,

  // Sert à définir un type invalide et donne un renseignement
  // sur la taille de l'enum.
  T_INVALID

}TYPEVAL;

class CType
{
private:

  TYPEVAL typeval;

  int ref_level;

public:

  CType()
  {
    this->typeval = T_INVALID;
    this->ref_level = -1;
  }

  CType(TYPEVAL typeval, int deref_level)
  {
    this->typeval = typeval;
    this->ref_level = ref_level;
  }
  
  TYPEVAL getTypeVal() { return this->typeval; };

  int getRef() { return this->ref_level; };
};

#endif/*TYPE_H*/
