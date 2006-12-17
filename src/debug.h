// vim: ts=2 tw=80

/** \file debug.h
 * \brief Header des fonctions de debug
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 07/12/2007
 */

#ifndef DEBUG_HEADER
#define DEBUG_HEADER

#define DEBUG(str) fprintf(stderr,"%s:%d in %s(), info: %s\n",__FILE__, __LINE__, __FUNCTION__, str)

/** \brief Positionne le niveau de debug debug_level.
 */
void debug_set_level(int*, char**);

/** \brief Simple fonction d'affichage sur stderr aidant au debug
*   \note Compil� par d�faut, activation sur passage du param�tre DEBUG_FLAG
*   (d�fini dans configuration.h).
*/
int debug_echo (char* str);

/** \brief Idem debug_echo, mais avec passage d'un int en param�tre.
 */
int debug_echoi (char* str, int);

/** \brief Idem debug_echoi, mais avec un float.
 */
float debug_echof (char* str, float);

/** \brief Fonction appel�e sur erreur critique du compilateur (en autre d�e au
 * syst�me sur lequel il s'ex�cute), ou lors de l'analyse du source. 
 * \param str Chaine affich�e
 * \param sanitizer Tente de d�sallouer 'proprement' les ressources
 * utilis�es avec la fonction pass�e en param�tre, puis quitte en flushant les
 * buffers. 
 */
void debug_critical_exit (char* str, void(*sanitizer)(void)); 

/** \brief Idem debug_critical_exit mais ne quitte pas, seulement utile lors du
 * d�veloppement, o� les crash abrupts sont tol�r�s.
 */
void debug_critical (char* str);

/** \brief Sauve les meubles et quitte, si possible. 
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
