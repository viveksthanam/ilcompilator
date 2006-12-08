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

/** \brief Fonction appelée sur erreur critique du compilateur (en autre dûe au
 * système sur lequel il s'exécute), ou lors de l'analyse du source. Tente de
 * désallouer 'proprement' les ressources utilisées avec sanitize(), puis quitte
 * en flushant les buffers, si on a pas planté d'ici là. Affiche un certain
 * nombre d'informations sur l'état de l'exécution du compilateur.
 */
void debug_critical_exit (char* str);

/** \brief Idem debug_critical_exit mais ne quitte pas, seulement utile lors du
 * développement, où les crash abrupts sont tolérés.
 */
void debug_critical (char* str);

/** \brief Sauve les meubles et quitte, si possible. Mouton noir de ce header
 * debug.h puisque il n'y a pas de rapport direct avec le debug, plutôt un lien
 * cause-conséquence.
 */
void sanitizer (void);

/** \brief Deprecated.
 */
int yyerror (char* str);

/** \brief Affiche la date de compilation au lancement du compilateur.
 */
void about(void);

#endif
/*debug.h*/
