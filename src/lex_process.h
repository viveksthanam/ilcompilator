//% vim: ts=2 tw=80

/** \file lex_process.h
 * \brief Header des (quelques) fonctions de traitement utilisées dans projet.l.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#ifndef HEADER_LEX_PROCESS
#define HEADER_LEX_PROCESS

/** \addtogroup LexProcessingFunctions
* Header des fonctions uniquement appelées dans Lex. Celles ci formatent les
* valeurs yyvalue et/ou yytext qui servent dans l'interface avec Yacc.
* @{
*/

/** \brief lex_process_getTinyStringID nous donne une version compacte d'une
 * instance de CStringID, puisque nous ne pouvons remonter que des entiers et
 * non pas des structures.
 */
int lex_process_getTinyStringID( char* string );

/** @} */

#endif
/*lex_process.h*/
