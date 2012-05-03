/* 
 * Original copyright:
 *   SumatraPDF project authors
 *   License: Simplified BSD (see COPYING.BSD) 
 * 
 * Modified by:
 *   Domenico Rotiroti
 *   License: GPL3 (see COPYING)
 */

#ifndef Utils_h
#define Utils_h

#if defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#endif

#ifdef DEBUG
#define _CRTDBG_MAP_ALLOC
#endif
#include <stdlib.h>
#ifdef DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

/* Few most common includes for C stdlib */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <locale.h>

#ifndef UNICODE
#include <sys/types.h>
#include <sys/stat.h>
#endif
#include <wchar.h>
#include <string.h>

/* Ugly name, but the whole point is to make things shorter.
   SAZA = Struct Allocate and Zero memory for Array
   (note: use operator new for single structs/classes) */
#define SAZA(struct_name, n) (struct_name *)calloc((n), sizeof(struct_name))

/* compile-time assert */
#define STATIC_ASSERT(exp, name) typedef int assert_##name [(exp) != false]

typedef unsigned char uint8;
typedef int16_t   int16;
typedef uint16_t uint16;
typedef int32_t   int32;
typedef uint32_t uint32;
typedef int64_t   int64;
typedef uint64_t uint64;

// for converting between big-/little-endian values and host endianness
// (the same macros could also be used for conversion in the opposite direction)
// TODO: swap definitions should we ever compile for big-endian architectures
typedef uint8 BYTE;
typedef uint16 WORD;
typedef uint32 DWORD;
typedef long LONG;
#define CP_UTF8 65001
#define MAKEWORD(a,b)	((WORD)(((BYTE)(a))|(((WORD)((BYTE)(b)))<<8)))
#define MAKELONG(a,b)	((LONG)(((WORD)(a))|(((DWORD)((WORD)(b)))<<16)))
#define LOWORD(l)	((WORD)((DWORD)(l)))
#define HIWORD(l)	((WORD)(((DWORD)(l)>>16)&0xFFFF))
#define LOBYTE(w)	((BYTE)(w))
#define HIBYTE(w)	((BYTE)(((WORD)(w)>>8)&0xFF))
/* --- */
#define BEtoHs(x) MAKEWORD(HIBYTE(x), LOBYTE(x))
#define BEtoHl(x) MAKELONG(BEtoHs(HIWORD(x)), BEtoHs(LOWORD(x)))
#define LEtoHs(x) (x)
#define LEtoHl(x) (x)

// useful for setting an 'invalid' state for size_t variables
#define MAX_SIZE_T (size_t)(-1)

STATIC_ASSERT(2 == sizeof(int16),   int16_is_2_bytes);
STATIC_ASSERT(2 == sizeof(uint16), uint16_is_2_bytes);
STATIC_ASSERT(4 == sizeof(int32),   int32_is_4_bytes);
STATIC_ASSERT(4 == sizeof(uint32),  uint32_is_4_bytes);
STATIC_ASSERT(8 == sizeof(int64),   int64_is_8_bytes);
STATIC_ASSERT(8 == sizeof(uint64),  uint64_is_8_bytes);

inline void *memdup(void *data, size_t len)
{
    void *dup = malloc(len);
    if (dup)
        memcpy(dup, data, len);
    return dup;
}
#define _memdup(ptr) memdup(ptr, sizeof(*(ptr)))
#endif