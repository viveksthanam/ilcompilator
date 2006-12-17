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

#include <string>

#include "instructionqueue.h"
#include "declarationqueue.h"

using namespace std;

/**\brief Classe charg�e d'�crire le code 3@ et de manipuler le
  * fichier de sortie.
  */
class CCodeWriter
{
private:

  /**\brief File descriptor sur le fichier de sortie.
    */
  FILE* foutput;

  string getStarsFromRefLevel(int ref_level);

public:

  /**\brief Constructeur par d�faut, ouvre le fichier
    *DEFAULT_OUTPUT_FILENAME en �criture.
    */
  CCodeWriter();

  /**\brief Constructeur par d�faut, ouvre le fichier
    *pass� en argument en �criture.
    *\param filename Fichier � ouvrir.
    */
  CCodeWriter(char* filename);

  ~CCodeWriter();

  /**\brief Ecrit dans le fichier les instructions de d�claration. On aurait pu
   * interdire toute �criture en cas d'erreur durant l'analyse du source, mais
   * nous ne voulons pas nous priver de la lecture du code cible g�n�r� jusqu'�
   * l'erreur.
   *\param declarations Pile des d�clarations � d�piler, pour remplir le fichier de sortie.
   */
  int writeDeclarations( CDeclarationQueue* declarations );

  /**\brief Ecrit dans le fichier les instructions. On aurait pu
   * interdire toute �criture en cas d'erreur durant l'analyse du source, mais
   * nous ne voulons pas nous priver de la lecture du code cible g�n�r� jusqu'�
   * l'erreur.
   *\param instructions Pile des instructions � vider pour remplir le fichier de sortie.
   */
  int writeInstructions( CInstructionQueue* instructions );
};

#endif/*CODEWRITER_H*/
