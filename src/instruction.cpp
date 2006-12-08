//% vim: ts=2 tw=80

/** \file instruction.cpp
 * \brief Définit la classe CInstruction chargée de stocker
 * les informations sur une instruction 'code 3@'.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#include "instruction.h"

CInstruction::CInstruction()
{
  return;
}

CInstruction::CInstruction( CSymbol* source, CSymbol* target )
{

  if( !source->getType().canConvertTo( target->getType() ) )
  {
    /**\todo Ajouter l'affichage du #warning : perte de données 
      * probable ici.*/
  }
  
  
  

  return;
}
