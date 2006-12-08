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

/** \brief Positionne le niveau de debug debug_level.
 */
void debug_set_level(int*, char**);

/** \brief Simple fonction d'affichage sur stderr aidant au debug
*   \note Compilé par défaut, activation sur passage du paramètre DEBUG_FLAG
*   (défini dans configuration.h).
*/
int debug_echo (char* str);

/** \brief Idem debug_echo, mais avec passage d'un int en paramètre.
 */
int debug_echoi (char* str, int);

/** \Brief Idem debug_echoi, mais avec float.
 */
float debug_echof (char* str, float);

#endif
/*debug.h*/
