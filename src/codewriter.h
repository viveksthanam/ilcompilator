//% vim: ts=2 tw=80

/** \file codewriter.h
 * \brief D�finition de la classe CCodeWriter charg�e
 * d'�crire le code 3@ � partir des piles de d�clarations
 * et de d'instructions.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 09/12/2006
 *
 */

#ifndef CODEWRITER_H
#define CODEWRITER_H

#include "instructionqueue.h"
#include "declarationqueue.h"

/**\brief Classe charg�e d'�crire le code 3@ et de manipuler le
  * fichier de sortie.
  */
class CCodeWriter
{
private:

  FILE* foutput;

public:

  /**\brief Constructeur par d�fault, ouvre le fichier
    *DEFAULT_OUTPUT_FILENAME en �criture.
    */
  CCodeWriter();

  /**\brief Constructeur par d�fault, ouvre le fichier
    *pass� en argument en �criture.
    *\param filename Fichier � ouvrir.
    */
  CCodeWriter(char* filename);

  ~CCodeWriter();

  /**\brief Ecrit dans le fichier les instructions de d�claration.
    *\param declarations Pile des d�clarations � vider 
    *pour remplir le fichier de sortie.
    */
  int writeDeclarations( CDeclarationQueue* declarations );

  /**\brief Ecrit dans le fichier les instructions. 
    *\param instructions Pile des instructions � vider 
    *pour remplir le fichier de sortie.
    */
  int writeInstructions( CInstructionQueue* instructions );
};

#endif/*CODEWRITER_H*/
