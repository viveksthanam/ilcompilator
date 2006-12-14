// vim: ts=2 tw=80

/** \file  type.h
 * \brief Fichier contenant la d�finition de la classe CType d�crivant
 *un type de variable dans le compilateur.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version 
 * \date 09/11/2006
 *
 */

#ifndef TYPE_H
#define TYPE_H

/**\brief Retourne un type de base compatible avec les
  * deux type pass�s en param�tre.
  *\param a Type de base
  *\param b Type de base
  *\return Un type compatible entre a et b.
  */
#define COMPATIBLEBASE( a, b ) ( ((int)(a) > (int)(b))?a:b )

/**\brief typedef enum listant les diff�rents types de base.
  *
  *\warning La position du type dans l'enumerate est importante
  *car on suppose que la conversion en entier de l'enumerate
  *permet de d�finir la r�gle suivante :
  *Si TYPEA > TYPEB alors on peut convertir TYPEA en TYPEB 
  *mais cela sera fait avec perte de donn�es.
  *Si TYPEA < TYPEB alors la conversion de TYPEA vers TYPEB
  * s'effectuera sans pertes.
  *
  */
typedef enum _TYPEVAL
{
  T_BOOL = 0,
  T_INT,
  T_FLOAT,

  // Sert � d�finir un type invalide et donne un renseignement
  // sur la taille de l'enum.
  T_INVALID

}TYPEVAL;

/**\brief Classe impl�mentant le type d'une variable.
  *
  * Le type d'une variable est la conjonction entre le type
  * de base de la variable (bool,int,float) et un entier
  * repr�sentant le niveau de r�f�rencement de cette variable.
  */
class CType
{
private:

  /**\brief Le type de base de la variable */
  TYPEVAL typeval;
  
  /**\brief Le niveau de r�f�rencement de la variable */
  int ref_level;

public:

  /**\brief Constructeur par d�fault g�n�rant un type invalide*/
  CType()
  {
    this->typeval = T_INVALID;
    this->ref_level = -1;
  }
  
  /**\brief Constructeur qui cr�e membre � membre la classe*/
  CType(TYPEVAL typeval, int ref_level)
  {
    this->typeval = typeval;
    this->ref_level = ref_level;
  }
 
  /**\brief Accesseur retournant le type de base */
  TYPEVAL getTypeVal() { return this->typeval; };

  /**\brief Accesseur retournant le niveau de r�f�rencement */
  int getRef() { return this->ref_level; };

  /**\brief Retourne un bool�en */
  bool canConvertTo( CType type )
  {
    if( this->ref_level != type.ref_level ) return false;

    if( (int)(this->typeval) < (int)(type.typeval) )
      return true;
    else
      return false;
  }
 
  bool operator == (const CType& type)
  {
    return ((this->typeval == type.typeval)
          &&(this->ref_level == type.ref_level));
    
  }

  /**\brief Retourne le type compatible entre les deux types.
    *\todo Changer ce mf�$$$ de commentaire.
    */
  const CType returnCompatible( const CType type )
  {
    if( this->typeval > type.typeval )
      return *this;
    else
      return type;
  }
 
};

   

#endif/*TYPE_H*/
