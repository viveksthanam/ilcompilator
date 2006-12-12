
#include "configuration.h"
#include "codewriter.h"

#include <iostream>

using namespace std;

extern int debug_level;

int main(void)
{
  int i;

  debug_level = 1;

  CCodeWriter writer(NULL);
  
  CDeclarationQueue dq;

  CInstructionQueue iq;

  CInstruction* pi = NULL;

  for(i=0;i<6;i++)
  {
    dq.addDeclaration( i, CType( (TYPEVAL)(i%T_INVALID), 0) ); 
  }
 
  for(i=0;i<5;i++)
  {
    pi = new CInstruction( OP3_CAST, i, i+1, 0,
                          CType((TYPEVAL)(i%T_INVALID),0) );

    iq.pushInstruction( pi );
  }

  for(i=0;i<5;i++)
  { 
    Operator op = (Operator)(i%OP0_INVALID);

    if( op == OP3_CAST ) op = OP3_ADD;

    pi = new CInstruction( op, i, i+1, i+2,
                          CType() );

    iq.pushInstruction( pi );
  }

  writer.writeDeclarations( &dq ); 

  writer.writeInstructions( &iq );

}
