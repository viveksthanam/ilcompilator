//% vim: ts=2 tw=80

/** \file codewriter.cpp 
 * \brief Implémentation de la classe CCodeWriter chargée
 * d'écrire le code 3@ à partir des piles de déclarations
 * et de d'instructions.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 09/12/2006
 *
 */

#include <iostream>

using namespace std;

#include "codewriter.h"

#include "configuration.h"
#include "stringtable.h"

#include "debug.h"

CCodeWriter::CCodeWriter( char* filename )
{
  if( !filename )
    filename = DEFAULT_OUTPUT_FILENAME;

  foutput = fopen(filename,"w");

  if( !foutput )
  {
    /**\todo Ajouter gestion d'erreur */
    debug_critical_exit("Impossible d'écrire le fichier de sortie.",NULL);
    return;
  }

  debug_echo("Production de code cible dans:");
  debug_echo(filename);
}

CCodeWriter::~CCodeWriter()
{
  if(foutput)
  {
    fclose( foutput );
    foutput = NULL;
  }

  debug_echo("Fin de l'écriture du code de sortie.");
}

string CCodeWriter::getStarsFromRefLevel( int ref_level )
{
  string str;
  int i;

  for(i=0;i<ref_level;i++)
    str += "*";

  return str;
}


int CCodeWriter::writeDeclarations( CDeclarationQueue* declarations )
{
  int id;
  int typeval;
  int ref_level;

  if(!declarations)
  {
    debug_critical("Impossible de défiler la file des déclarations");
    return 0;
  }

  while( !(declarations->empty()) )
  {
    id = (int)( (declarations->front())->id );
    typeval = (int)( (declarations->front())->type.getTypeVal() );
    ref_level = (int)( (declarations->front())->type.getRef() );

    fprintf(foutput, "%s %s%s%d%s",
            string_types[typeval],  // La chaine associée au type
            getStarsFromRefLevel(ref_level).c_str(), // Les étoiles
            INSTRUCTION_BASE_NAME,  // Le nom de base
            id,                     // L'id
            INSTRUCTION_SEPARATOR); // Le séparateur d'instructions

    declarations->pop();
  }

  return 1;
}

int CCodeWriter::writeInstructions( CInstructionQueue* instructions )
{
  CInstruction* p_instr;

  if(!instructions)
  {
    debug_critical("Impossible de défiler la file des instructions");
    return 0;
  }

  while( !(instructions->empty()) )
  {
    p_instr = instructions->front();

    cerr<<"CW op="<<p_instr->getOperator()
        <<" op1="<<p_instr->getOperand_1()
        <<" op2="<<p_instr->getOperand_2()
        <<" op3="<<p_instr->getOperand_3()
        <<" cast="<<p_instr->getCastType().getTypeVal()
        <<","<<p_instr->getCastType().getRef()
        <<" label="<<p_instr->getLabel()
        <<endl;

    // Gestion des cas spéciaux
    switch( p_instr->getOperator() ) 
    {
      case OP3_CAST:

        fprintf( foutput, string_operators[p_instr->getOperator()],
                  INSTRUCTION_BASE_NAME,
                  p_instr->getOperand_1(),
                  string_types[p_instr->getCastType().getTypeVal()],
                  getStarsFromRefLevel(p_instr->getCastType().getRef()).c_str(),
                  INSTRUCTION_BASE_NAME,
                  p_instr->getOperand_2(),
                  INSTRUCTION_SEPARATOR);
         break;

       case OP2_EQU:
         
        fprintf( foutput, string_operators[p_instr->getOperator()],
                  INSTRUCTION_BASE_NAME,
                  p_instr->getOperand_1(),
                  INSTRUCTION_BASE_NAME,
                  p_instr->getOperand_2(),
                  INSTRUCTION_SEPARATOR);
         break;

       case OP2_EQU_CONST_RVALUE_BOOL:

         fprintf( foutput, string_operators[p_instr->getOperator()],
                  INSTRUCTION_BASE_NAME,
                  p_instr->getOperand_1(),
                  p_instr->getBoolConstValue(),
                  INSTRUCTION_SEPARATOR);
         break;

       case OP2_EQU_CONST_RVALUE_INT:

         fprintf( foutput, string_operators[p_instr->getOperator()],
                  INSTRUCTION_BASE_NAME,
                  p_instr->getOperand_1(),
                  (int)p_instr->getIntConstValue(),
                  INSTRUCTION_SEPARATOR);
         break;

       case OP2_EQU_CONST_RVALUE_FLOAT:

         fprintf( foutput, string_operators[p_instr->getOperator()],
                  INSTRUCTION_BASE_NAME,
                  p_instr->getOperand_1(),
                  p_instr->getFloatConstValue(),
                  INSTRUCTION_SEPARATOR);
         break;

       case OP1_GOTO:
      
          fprintf( foutput, string_operators[p_instr->getOperator()],
                   INSTRUCTION_LABEL_NAME,
                   p_instr->getLabel(),
                   INSTRUCTION_SEPARATOR);
         break;

       case OP2_NOT:
         fprintf( foutput, string_operators[p_instr->getOperator()],
                   INSTRUCTION_BASE_NAME,
                   p_instr->getOperand_1(),
                   INSTRUCTION_BASE_NAME,
                   p_instr->getOperand_2(),
                   INSTRUCTION_SEPARATOR);
          break;

       case OP1_LABEL:
          
          fprintf( foutput, string_operators[p_instr->getOperator()],
                   INSTRUCTION_LABEL_NAME,
                   p_instr->getLabel(),
                   INSTRUCTION_EOL);
         break;

       case OP2_IF:
      
          fprintf( foutput, string_operators[p_instr->getOperator()],
                   INSTRUCTION_BASE_NAME,
                   p_instr->getOperand_1(),
                   INSTRUCTION_LABEL_NAME,
                   p_instr->getLabel(),
                   INSTRUCTION_SEPARATOR);
         break;

       case OP2_STAR:

          fprintf( foutput, string_operators[p_instr->getOperator()],
                   INSTRUCTION_BASE_NAME,
                   p_instr->getOperand_1(),
                   INSTRUCTION_BASE_NAME,
                   p_instr->getOperand_2(),
                   INSTRUCTION_SEPARATOR);


          break;

       default:

         fprintf( foutput, string_operators[p_instr->getOperator()],
                  INSTRUCTION_BASE_NAME,
                  p_instr->getOperand_1(),
                  INSTRUCTION_BASE_NAME,
                  p_instr->getOperand_2(),
                  INSTRUCTION_BASE_NAME,
                  p_instr->getOperand_3(),
                  INSTRUCTION_SEPARATOR);
          break;
    }                

    delete (instructions->front());

    instructions->pop();
  }

  return 1;
}
