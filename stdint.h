/*
 * Copyright (c) 2002,2004,2005,2007 Marek Michalkiewicz
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
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.
 */

#ifndef _STDINT_H_
#define _STDINT_H_

/** @file */
/** @defgroup avr_stdint <stdint.h>: Standard Integer Types
    @code #include <stdint.h> @endcode

    This header file file contains definitions for integer types with 
    specified widths. */

#ifdef __cplusplus
extern "C" {
#endif

// =========================================================================
// 🔢 TYPES ENTIERS À LARGEUR EXACTE (Exact-width integer types)
// =========================================================================

typedef signed char        int8_t;   // Entier signé sur 8 bits (-128 à 127)
typedef unsigned char      uint8_t;  // Entier non signé sur 8 bits (0 à 255)

typedef signed int         int16_t;  // Entier signé sur 16 bits (-32768 à 32767)
typedef unsigned int       uint16_t; // Entier non signé sur 16 bits (0 à 65535)

typedef signed long int    int32_t;  // Entier signé sur 32 bits
typedef unsigned long int  uint32_t; // Entier non signé sur 32 bits (Idéal adresses/système)

typedef signed long long   int64_t;  // Entier signé sur 64 bits
typedef unsigned long long uint64_t; // Entier non signé sur 64 bits

// =========================================================================
// 🚀 TYPES ENTIERS LES PLUS RAPIDES (Fastest minimum-width integer types)
// =========================================================================

typedef int8_t             int_fast8_t;
typedef uint8_t            uint_fast8_t;

typedef int16_t            int_fast16_t;
typedef uint16_t           uint_fast16_t;

typedef int32_t            int_fast32_t;
typedef uint32_t           uint_fast32_t;

typedef int64_t            int_fast64_t;
typedef uint64_t           uint_fast64_t;

// =========================================================================
// 📍 TYPES POUR CAPACITÉ DE POINTEURS (Integer types capable of holding object pointers)
// =========================================================================

typedef int16_t            intptr_t;  // Sur AVR/Arduino Uno, un pointeur fait 16 bits
typedef uint16_t           uintptr_t;

// =========================================================================
// 👑 TYPES ENTIERS MAXIMUMS (Greatest-width integer types)
// =========================================================================

typedef int64_t            intmax_t;
typedef uint64_t           uintmax_t;

// =========================================================================
// 📊 LIMITES DES VALEURS (VALEURS MAX ET MIN)
// =========================================================================

#define INT8_MIN               (-128)
#define INT8_MAX               (127)
#define UINT8_MAX              (255)

#define INT16_MIN              (-32767-1)
#define INT16_MAX              (32767)
#define UINT16_MAX             (65535)

#define INT32_MIN              (-2147483647L-1L)
#define INT32_MAX              (2147483647L)
#define UINT32_MAX             (4294967295UL)

#define INT64_MIN              (-9223372036854775807LL-1LL)
#define INT64_MAX              (9223372036854775807LL)
#define UINT64_MAX             (18446744073709551615ULL)

#define INTMAX_MIN             INT64_MIN
#define INTMAX_MAX             INT64_MAX
#define UINTMAX_MAX            UINT64_MAX

#ifdef __cplusplus
}
#endif

#endif /* _STDINT_H_ */
