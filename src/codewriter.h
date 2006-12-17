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

#include <string>

#include "instructionqueue.h"
#include "declarationqueue.h"

using namespace std;

/**\brief Classe chargée d'écrire le code 3@ et de manipuler le
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

  /**\brief Constructeur par défaut, ouvre le fichier
    *DEFAULT_OUTPUT_FILENAME en écriture.
    */
  CCodeWriter();

  /**\brief Constructeur par défaut, ouvre le fichier
    *passé en argument en écriture.
    *\param filename Fichier à ouvrir.
    */
  CCodeWriter(char* filename);

  ~CCodeWriter();

  /**\brief Ecrit dans le fichier les instructions de déclaration. On aurait pu
   * interdire toute écriture en cas d'erreur durant l'analyse du source, mais
   * nous ne voulons pas nous priver de la lecture du code cible généré jusqu'à
   * l'erreur.
   *\param declarations Pile des déclarations à dépiler, pour remplir le fichier de sortie.
   */
  int writeDeclarations( CDeclarationQueue* declarations );

  /**\brief Ecrit dans le fichier les instructions. On aurait pu
   * interdire toute écriture en cas d'erreur durant l'analyse du source, mais
   * nous ne voulons pas nous priver de la lecture du code cible généré jusqu'à
   * l'erreur.
   *\param instructions Pile des instructions à vider pour remplir le fichier de sortie.
   */
  int writeInstructions( CInstructionQueue* instructions );
};

#endif/*CODEWRITER_H*/
