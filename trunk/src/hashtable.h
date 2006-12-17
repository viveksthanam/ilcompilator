// vim: ts=2 tw=80

/** \file hashtable.cpp
 * \brief Implémentation de la classe CHashtable, table de hachage
 *        permettant de fournir un StringID unique à une chaine et 
 *        d'y acceder ensuite avec une complexité faible.
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
  * à une chaîne de caractères un identifiant unique et de stocker
  * la chaîne de caractère pour y acceder par la suite avec une complexité
  * convenable.
  */
class CHashtable
{
private:

  /** \brief Table contenant les chaînes */
  vector<string> table[HASHTABLE_SIZE];
 
  /** \brief Retourne le hash (int) de la chaine passée en paramètre.*/
  int getHashFromString( const char* );

public:

  CHashtable();

  /** \brief Retourne la chaine associée 
    * au CStringID passée en paramètre
    */
  string getStringFromStringID( CStringID );
  
 /** \brief Retourne le CStringID associé
    * à la chaine passée en paramètre
    */
  CStringID getStringIDFromString( string );
  
};

#endif/*HASHTABLE_H*/
