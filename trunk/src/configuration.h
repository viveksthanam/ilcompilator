//% vim: ts=2 tw=80

/** \file configuration.h
 * \brief Contient les configurations des diff�rents
 * �l�ments du compilateur.
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

/** \brief D�finit le niveau maximum de r�f�rencement.*/
#define MAX_REFERENCE_LEVEL 128

/** \brief Niveau de r�f�rencement par d�faut */
#define DEFAULT_REF_LVL 0  

/** \brief Nom par d�fault du fichier de sortie.*/
#define DEFAULT_OUTPUT_FILENAME "output.3a"

#define INSTRUCTION_BASE_NAME "var"
#define INSTRUCTION_SEPARATOR ";\n"

/** \brief Param�tre d�clenchant le mode debug.
 */
#define DEBUG_FLAG "-d"

/* Fonctionnement interne, ne devrait pas �tre touch�... <fear!> */
#define DEBUG_FLAG_POSITION 0

/** \brief Valeurs retourn�e dans Yacc ($$) lorsque un token TRUE
 * ou FALSE est rencontr�.
 */
#define DEF_TRUE 1
#define DEF_FALSE 0

/** \brief Mode verbeux de Yacc */
#define YYERROR_VERBOSE

#endif
/*configuration.h*/
