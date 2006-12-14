//% vim: ts=2 tw=80

/** \file label.h
 * \brief Gère les labels
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 14/12/2006
 *
 */

#ifndef LABEL_H
#define LABEL_H

class CLabel
{
private:
  int n;

public:

  CLabel();
  int get();
  void inc();
};

#endif/*LABEL_H*/
