//% vim: ts=2 tw=80

/** \file label.cpp 
 * \brief G�re les labels
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 14/12/2006
 *
 */

#include "label.h"

CLabel::CLabel()
{
  this->n=0;
}

int CLabel::get()
{
  return this->n;
}

void CLabel::inc()
{
  (this->n)++;
}
