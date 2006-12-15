//% vim: ts=2 tw=80

/** \file label.cpp 
 * \brief Gère les labels
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

void CLabel::push()
{
  n += 2;

  labels.push( COUPLE( n, n+1 ) );
}

void CLabel::pop()
{
  labels.pop();
}

int CLabel::getThen()
{
  return (labels.top()).label_then;
}

int CLabel::getElse()
{
  return (labels.top()).label_else;
}

