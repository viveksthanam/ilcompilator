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
  T_FLOAT

}TYPEVAL;

class CType
{
private:

  TYPEVAL typeval;

  int deref_level;

public:

  TYPEVAL getTypeVal() { return this->typeval; };

  int getDeref() { return this->deref_level; };
};

#endif/*TYPE_H*/
