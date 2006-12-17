//% vim: ts=2 tw=80

/** \file stringtable.h
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
{"%s%d = %s%d + %s%d%s",//OP3_ADD
"%s%d = %s%d - %s%d%s", //OP3_SUB
"%s%d = %s%d * %s%d%s", //OP3_MUl
"%s%d = %s%d / %s%d%s", //OP3_DIV

"%s%d = %s%d && %s%d%s",   //OP3_AND
"%s%d = %s%d || %s%d%s",   //OP3_OR

"%s%d = %s%d == %s%d%s",   //OP3_EQL
"%s%d = %s%d != %s%d%s",   //OP3_NEQ
"%s%d = %s%d < %s%d%s",    //OP3_LOW
"%s%d = %s%d > %s%d%s",    //OP3_GRT

"%s%d = !%s%d%s",         //OP2_NOT
"%s%d = -%s%d%s",         //OP2_NEG

"%s%d = %s%d%s",        //OP3_EQU
"%s%d = %d%s",          //OP3_EQU_CONST_RVALUE_BOOL
"%s%d = %d%s",          //OP3_EQU_CONST_RVALUE_INT
"%s%d = %f%s",          //OP3_EQU_CONST_RVALUE_FLOAT

"%s%d = (%s%s)%s%d%s",    //OP3_CAST

"%s%d:%s",                  //OP1_LABEL
"goto %s%d%s",              //OP1_GOTO
"if(%s%d) goto %s%d%s",      //OP2_IF
"%s%d = *%s%d%s"         //OP2_STAR
};

#endif/*STRINGTABLE_H*/
