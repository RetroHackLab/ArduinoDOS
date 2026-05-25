/*
 * Copyright (c) 2002, 2007 Marek Michalkiewicz
 * All rights reserved.
 *
 * Redistribution and use in binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 */

#ifndef _AVR_STDDEF_H_
#define _AVR_STDDEF_H_

// Empêche les conflits si size_t est déjà défini par l'IDE
#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;  // Type indispensable pour mesurer la taille des fichiers/blocs
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef signed int ptrdiff_t; // Utilisé pour calculer la distance entre deux pointeurs mémoire
#endif

// Définition standard et propre du pointeur NUL
#ifndef NULL
#define NULL ((void *)0)
#endif

// Définition du type de caractère large (requis pour la compatibilité C/C++)
#ifndef _WCHAR_T
#define _WCHAR_T
typedef char wchar_t;
#endif

// Macro système bas niveau pour localiser l'offset d'une variable dans une structure
#undef offsetof
#define offsetof(type, member) __builtin_offsetof(type, member)

#endif /* _AVR_STDDEF_H_ */
