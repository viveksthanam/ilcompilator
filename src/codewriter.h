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

/**\brief Classe charg�e d'�crire le code 3@ et de manipuler le
  * fichier de sortie.
  */
class CCodeWriter
{
private:

  FILE* foutput;

public:

  CCodeWriter();
  CCodeWriter(char*);
  ~CCodeWriter();

};

#endif/*CODEWRITER_H*/
