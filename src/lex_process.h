//% vim: ts=2 tw=80

/** \file lex_process.h
 * \brief Header des fonctions de traitement utilis�es dans projet.l.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 08/12/2006
 *
 */

#ifndef HEADER_LEX_PROCESS
#define HEADER_LEX_PROCESS

/** \addtogroup LexProcessingFunctions
* Header des fonctions appel�es dans le fichier Lex. Celles-ci formatent les
* valeurs yyvalue, yytext, yylval_float (etc) qui servent dans l'interface avec
* Yacc.
* @{
*/

/** \brief lex_process_getTinyStringID nous donne une version 'compacte' d'une
 * instance de CStringID, puisque nous ne remontons pas des entiers et
 * des structures. 
 * \param my_HT Pointeur sur notre table de hash.
 * \param str Correspond � yytext ayant 'match�' un ID.
 * \return Entier repr�sentant un CStringID.
 */
int lex_process_getTinyStringID( CHashtable* my_HT, char* str );

/** \brief Alias de strtoi, mode verbeux.
 */
int lex_process_atoi ( char* str );

/** \brief Alias de strtof, mode verbeux.
 */
float lex_process_atof ( char* str ); 

/** @} */

#endif
/*lex_process.h*/
