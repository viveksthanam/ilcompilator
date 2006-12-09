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

CCodeWriter::CCodeWriter()
{
  CCodeWriter( DEFAULT_OUTPUT_FILENAME );
}

CCodeWriter::CCodeWriter( char* filename )
{
  foutput = fopen(filename,"w");
}

CCodeWriter::~CCodeWriter()
{

}
