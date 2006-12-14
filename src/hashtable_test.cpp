//% vim: ts=2 tw=80

/** \file codewriter_test.cpp 
 * \brief Fichier contenant le code chargé de tester le
 *fonctionnement de CHashtable.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#include <iostream>

#include "hashtable.h"

int main(void)
{
  CHashtable ht;
  CStringID sid;


  cerr<<"Go !"<<endl;

  char buf[128];

  string plouf = "kwain";

  for(int i=0;i<0;i++)
  {

    sprintf(buf,"LOUTRE%d",i);

    sid = ht.getStringIDFromString(buf);
    cerr<<buf<<"\n";
    cerr<<"h="<<sid.hash<<" d="<<sid.depth<<endl;
    cerr<<"val="<<sid.toInt()<<endl;

  }

  return 0;
}
