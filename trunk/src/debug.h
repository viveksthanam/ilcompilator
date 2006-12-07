/* protos des fonctions de debug */
#ifndef DEBUG_HEADER
#define DEBUG_HEADER

// vim: ts=2 tw=80

/** \file debug.h
 * \brief Header des fonctions de debug
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 07/12/2007
 */

/** \brief Simple fonction d'affichage sur stdout aidant au debug
*   \note Aucun effet si DEBUG_ECHO n'est pas positionn�e (dans configuration.h).
* */
int debug_echo (char* string);

#endif
/*debug.h*/
