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
