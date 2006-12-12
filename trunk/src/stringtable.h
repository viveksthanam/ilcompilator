//% vim: ts=2 tw=80

/** \file stringtable
 * \brief Contient les correspondances entre les 
 * types, les opérateurs et les instructions 3@.
 * \author <brossill@enseirb.fr> <lerouxj@enseirb.fr>
 * \version
 * \date 09/12/2006
 *
 */

#ifndef STRINGTABLE_H
#define STRINGTABLE_H

char* string_types[T_INVALID] = 
{"bool",
 "int",
 "float" };

char* string_operators[OP0_INVALID] =
{"%s%d = %s%d + %s%d%s",
"%s%d = %s%d - %s%d%s",
"%s%d = %s%d * %s%d%s",
"%s%d = %s%d / %s%d%s",
"%s%d = %s%d%s",
"%s%d = (%s)%s%d%s"
};

#endif/*STRINGTABLE_H*/
