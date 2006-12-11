/* protos des fonctions de debug */
#ifndef DEBUG_HEADER
#define DEBUG_HEADER

#define DEBUG(str) fprintf(stderr,"%s:%d in %s(), info: %s\n",__FILE__, __LINE__, __FUNCTION__, str)

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
*   \note Compil� par d�faut, activation sur passage du param�tre DEBUG_FLAG
*   (d�fini dans configuration.h).
*/
int debug_echo (char* str);

/** \brief Idem debug_echo, mais avec passage d'un int en param�tre.
 */
int debug_echoi (char* str, int);

/** \brief Idem debug_echoi, mais avec float.
 */
float debug_echof (char* str, float);

/** \brief Fonction appel�e sur erreur critique du compilateur (en autre d�e au
 * syst�me sur lequel il s'ex�cute), ou lors de l'analyse du source. Tente de
 * d�sallouer 'proprement' les ressources utilis�es avec sanitize(), puis quitte
 * en flushant les buffers, si on a pas plant� d'ici l�. Affiche un certain
 * nombre d'informations sur l'�tat de l'ex�cution du compilateur.
 */
void debug_critical_exit (char* str);

/** \brief Idem debug_critical_exit mais ne quitte pas, seulement utile lors du
 * d�veloppement, o� les crash abrupts sont tol�r�s.
 */
void debug_critical (char* str);


/** \brief Affiche un message cens� exprimer toute la d�tresse
  *actuellement ressentie par le programme, sauve les meubles en
  *appellant une fonction fournie par l'utilisateur et quitte avec
  *pertes et fracas (explosions, flammes et musique fournis sur
  *demande)
  */
void debug_critical_exit( char* str, void(*sanitizer)(void)  );

/** \brief Deprecated.
 */
int yyerror (char* str);

/** \brief Affiche la date de compilation au lancement du compilateur.
 */
void about(void);

#endif
/*debug.h*/
