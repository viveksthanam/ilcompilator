//% vim: ts=2 tw=80

/** \file configuration.h
 * \brief Contient les configurations des différents
 * éléments du compilateur.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 07/12/2006
 *
 */

#ifndef HEADER_CONFIG
#define HEADER_CONFIG

/** \brief Taille de la table de hash.
 */
#define HASHTABLE_SIZE 100

/** \brief Pour activer le verbose.
 */
#define DEBUG_ECHO

/** \brief Valeurs retournée dans Yacc ($$) lorsque un token TRUE
 * ou FALSE est rencontré.
 */
#define DEF_TRUE 1
#define DEF_FALSE 0

/** \note Mode verbeux de Yacc */
#define YYERROR_VERBOSE

#endif
/*configuration.h*/
