//% vim: ts=2 tw=80

/** \file codewriter.cpp 
 * \brief Impl�mentation de la classe CCodeWriter charg�e
 * d'�crire le code 3@ � partir des piles de d�clarations
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
    /**\todo Ajouter l'erreur quand debug sera nettoy� */
    debug_critical_exit("Impossible d'�crire le fichier de sortie.",NULL);
    return;
  }

  debug_echo("D�but de l'�criture du code de sortie dans le fichier :");
  debug_echo(filename);
}

CCodeWriter::~CCodeWriter()
{
  if(foutput)
  {
    fclose( foutput );
    foutput = NULL;
  }

  debug_echo("Fin de l'�criture du code de sortie.");
}

int CCodeWriter::writeDeclarations( CDeclarationQueue* declarations )
{
  int id;
  int typeval;

  if(!declarations)
  {
    debug_echo("Impossible de d�filer la file des d�clarations");
    return 0;
  }

  while( !(declarations->empty()) )
  {
    id = (int)( (declarations->front())->id );

    typeval = (int)( (declarations->front())->type.getTypeVal() );

    fprintf(foutput, "%s %s%d%s",
            string_types[typeval],       // La chaine associ�e au type
            INSTRUCTION_BASE_NAME,  // Le nom de base
            id,                     // L'id
            INSTRUCTION_SEPARATOR); // Le s�parateur d'instructions

    declarations->pop();
  }

  return 1;
}

int CCodeWriter::writeInstructions( CInstructionQueue* instructions )
{
  CInstruction* p_instr;

  if(!instructions)
  {
    debug_echo("Impossible de d�filer la file des instructions");
    return 0;
  }

  while( !(instructions->empty()) )
  {
    p_instr = instructions->front();

    // Gestion des cas sp�ciaux
    switch( p_instr->getOperator() ) 
    {
      case OP3_CAST:

        fprintf( foutput, string_operators[p_instr->getOperator()],
                  INSTRUCTION_BASE_NAME,
                  p_instr->getOperand_1(),
                  string_types[p_instr->getCastType().getTypeVal()],
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
    
    instructions->pop();
  }

  return 1;
}
