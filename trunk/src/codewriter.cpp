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

#include "codewriter.h"

#include "configuration.h"
#include "debug.h"

CCodeWriter::CCodeWriter()
{
  CCodeWriter( DEFAULT_OUTPUT_FILENAME );
}

CCodeWriter::CCodeWriter( char* filename )
{
  foutput = fopen(filename,"w");

  if( !foutput )
  {
    debug_critical_exit("Impossible d'�crire le fichier de sortie.");
    return;
  }

  debug_echo("D�but de l'�criture du code de sortie dans le fichier :");
  debug_echo(filename);
}

CCodeWriter::~CCodeWriter()
{
  if(!foutput)
    fclose( foutput );

  debug_echo("Fin de l'�criture du code de sortie.");
}

int writeDeclarations( CDeclarationQueue* declarations )
{

}

int writeInstructions( CInstructionQueue* instructions )
{

}

