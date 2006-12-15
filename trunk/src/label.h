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

#include <stack>

using namespace std;

class CLabel
{
private:
  int n;

  typedef struct _COUPLE
  {
    _COUPLE(int a, int b)
    {
      label_then = a;
      label_else = b;
    }

    int label_then;
    int label_else;
  }COUPLE;

  stack<COUPLE> labels;

public:

  CLabel();
  void push();
  void pop();
  int getThen();
  int getElse();
};

#endif/*LABEL_H*/
