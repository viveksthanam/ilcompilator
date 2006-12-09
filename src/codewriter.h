//% vim: ts=2 tw=80

/** \file codewriter.h
 * \brief Définition de la classe CCodeWriter chargée
 * d'écrire le code 3@ à partir des piles de déclarations
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

/**\brief Classe chargée d'écrire le code 3@ et de manipuler le
  * fichier de sortie.
  */
class CCodeWriter
{
private:

  FILE* foutput;

public:

  /**\brief Constructeur par défault, ouvre le fichier
    *DEFAULT_OUTPUT_FILENAME en écriture.
    */
  CCodeWriter();

  /**\brief Constructeur par défault, ouvre le fichier
    *passé en argument en écriture.
    *\param filename Fichier à ouvrir.
    */
  CCodeWriter(char* filename);

  ~CCodeWriter();

  /**\brief Ecrit dans le fichier les instructions de déclaration.
    *\param declarations Pile des déclarations à vider 
    *pour remplir le fichier de sortie.
    */
  int writeDeclarations( CDeclarationQueue* declarations );

  /**\brief Ecrit dans le fichier les instructions. 
    *\param instructions Pile des instructions à vider 
    *pour remplir le fichier de sortie.
    */
  int writeInstructions( CInstructionQueue* instructions );
};

#endif/*CODEWRITER_H*/
