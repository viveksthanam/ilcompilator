// vim: ts=2 tw=80

/** \file contextstack.h
 * \brief Définit la classe CContextStack qui contiendra
 * les différents symboles et ajoutera une information
 * sur le context du dit symbole.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 07/12/2006
 *
 */

#ifndef CONTEXTSTACK_H
#define CONTEXTSTACK_H

#include <vector>
#include <stack>

#include "symbol.h"
#include "type.h"

// Pour vector et stack
using namespace std;

/** \brief Classe contenant la pile des symboles et gérant
  * la sauvegarde et la restauration des contextes.
  * 
  * La classe contient le membre symbols contenant 
  * les pointeurs vers les symboles du compilateur.
  * Le membre size_stack est une pile des tailles
  * courantes au moment de la sauvegarde du contexte.
  */
class CContextStack
{
private:
  
  /**\brief Vecteur des pointeurs vers les symboles */
  vector<CSymbol*> symbols;

  /**\brief Pile des tailles des contextes */
  stack<int> size_stack;

  /**\brief Indices du prochain SymbolID à allouer */
  int n;

public:

  CContextStack();

  ~CContextStack();

  /**\brief Créé et empile un symbole dans la pile des contextes
    *\param sid CStringID associé au nom du symbole.
    *\param type Classe CType décrivant le type du symbole.
    *\return Un CSymbol* pointant vers le symbole ainsi créé.
    *Renvoie NULL dans le cas d'un echec à la création.
    */
  CSymbol* addSymbol( CStringID sid, CType type);

  /**\brief Empile un symbole dans la pile des contextes
    *\param symbol CSymbol* à empiler.
    */
  void pushSymbol( CSymbol* symbol );
  
  /**\brief Retourne un pointeur vers le symbole ayant
    * pour SymbolID le SymbolID passé en paramètre et étant
    * présent dans le contexte courant.
    *\param id SymbolID à rechercher.
    *\return Pointeur vers le SymbolID ainsi trouvé. Retourne
    * NULL si le symbole n'est pas trouvé dans la pile.
    */
  CSymbol* getSymbolInContext( SymbolID id );

  /**\brief Retourne un pointeur vers le premier symbole dans
    * la pile ayant pour CStringID le CStringID passé en paramètre
    * et étant présent dans le contexte courant.
    *\param csid CStringID à rechercher.
    *\return Pointeur vers le SymbolID ainsi trouvé. Retourne
    * NULL si le symbole n'est pas trouvé dans la pile.
    */
  CSymbol* getSymbolInContext( CStringID csid );

  /**\brief Retourne un pointeur vers le symbole ayant
    * pour SymbolID le SymbolID passé en paramètre.
    *\param sid SymbolID à rechercher.
    *\return Pointeur vers le SymbolID ainsi trouvé. Retourne
    * NULL si le symbole n'est pas trouvé dans la pile.
    */
  CSymbol* getSymbol( SymbolID sid );

  /**\brief Retourne un pointeur vers le premier symbole dans
    * la pile ayant pour CStringID le CStringID passé en paramètre.
    *\param csid CStringID à rechercher.
    *\return Pointeur vers le SymbolID ainsi trouvé. Retourne
    * NULL si le symbole n'est pas trouvé dans la pile.
    */
  CSymbol* getSymbol( CStringID csid );

  /**\brief Sauvegarde le contexte courant et en empile un nouveau
    */
  void saveContext(void);

  /**\brief Restore le contexte précédent et dépile le courant
    */
  void restoreContext(void);
};

#endif/*CONTEXTSTACK_H*/
