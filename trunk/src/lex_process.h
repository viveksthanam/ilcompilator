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
* Header des fonctions appelées dans le fichier Lex. Celles-ci formatent les
* valeurs yyvalue, yytext, yylval_float (etc) qui servent dans l'interface avec
* Yacc. Convention de nommage des fonctions : [lex_process][utilisation]().
* @{
*/

/** \brief lex_process_getTinyStringID nous donne une version 'compacte' d'une
 * instance de CStringID, puisque nous ne pouvons pas encore remonter des entiers et
 * des structures. 
 * \param CHashtable* my_HT Pointeur sur notre table de hash.
 * \param char* string Correspond à yytext ayant 'matché' un ID.
 * \return Entier représentant un CStringID.
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
