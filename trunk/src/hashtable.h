// vim: ts=2 tw=80

/** \file hashtable.cpp
 * \brief Impl�mentation de la classe CHashtable, table de hachage
 *        permettant de fournir un StringID unique � une chaine et 
 *        d'y acceder ensuite avec une complexit� faible.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version 
 * \date 07/12/2006
 *
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

#include "hashtable.h"
#include "stringid.h"

using namespace std;


/** \brief Classe contenant la table de hashage permettant d'allouer
  * � une cha�ne de caract�res un identifiant unique et de stocker
  * la cha�ne de caract�re pour y acceder par la suite avec une complexit�
  * convenable.
  */
class CHashtable
{
private:

  /** \brief Table contenant les cha�nes */
  vector<string> table[HASHTABLE_SIZE];
 
  /** \brief Retourne le hash (int) de la chaine pass�e en param�tre.*/
  int getHashFromString( const char* );

public:

  CHashtable();

  /** \brief Retourne la chaine associ�e 
    * au CStringID pass�e en param�tre
    */
  string getStringFromStringID( CStringID );
  
 /** \brief Retourne le CStringID associ�
    * � la chaine pass�e en param�tre
    */
  CStringID getStringIDFromString( string );
  
};

#endif/*HASHTABLE_H*/
