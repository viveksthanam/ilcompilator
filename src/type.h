// vim: ts=2 tw=80

/** \file 
 * \brief 
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 
 *
 */

#ifndef TYPE_H
#define TYPE_H

/**\brief typedef enum listant les différents types de base.
  *
  *\warning La position du type dans l'enumerate est importante
  *car on suppose que la conversion en entier de l'enumerate
  *permet de définir la règle suivante :
  *Si TYPEA > TYPEB alors on peut convertir TYPEA en TYPEB 
  *mais cela sera fait avec perte de données.
  *Si TYPEA < TYPEB alors la conversion de TYPEA vers TYPEB
  * s'effectuera sans pertes.
  *
  */
typedef enum _TYPEVAL
{
  T_BOOL = 0,
  T_INT,
  T_FLOAT,

  // Sert à définir un type invalide et donne un renseignement
  // sur la taille de l'enum.
  T_INVALID

}TYPEVAL;

/**\brief Classe implémentant le type d'une variable.
  *
  * Le type d'une variable est la conjonction entre le type
  * de base de la variable (bool,int,float) et un entier
  * représentant le niveau de référencement de cette variable.
  */
class CType
{
private:

  /**\brief Le type de base de la variable */
  TYPEVAL typeval;
  
  /**\brief Le niveau de référencement de la variable */
  int ref_level;

public:

  /**\brief Constructeur par défault générant un type invalide*/
  CType()
  {
    this->typeval = T_INVALID;
    this->ref_level = -1;
  }
  
  /**\brief Constructeur qui créant membre à membre la classe*/
  CType(TYPEVAL typeval, int deref_level)
  {
    this->typeval = typeval;
    this->ref_level = ref_level;
  }
 
  /**\brief Accesseur retournant le type de base */
  TYPEVAL getTypeVal() { return this->typeval; };

  /**\brief Accesseur retournant le niveau de référencement */
  int getRef() { return this->ref_level; };

  /**\brief Retourne un booléen */
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

  /**\brief Retourne un type de base compatible avec les
    * deux type passés en paramètre.
    *\param a Type de base
    *\param b Type de base
    *\return Un type compatible entre a et b.
    */
  TYPEVAL returnCompatibleBase( TYPEVAL a, TYPEVAL b )
  {
    if( (int)a > (int)b )
      return a;
    else
      return b;
  }
 
};

   

#endif/*TYPE_H*/
