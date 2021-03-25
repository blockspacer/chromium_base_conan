#pragma once

#ifndef __has_include
#error "__has_include not supported"
#endif // __has_include

#ifndef HAVE_INTTYPES_H
#if __has_include(<inttypes.h>)
#define HAVE_INTTYPES_H 1
#endif // __has_include
#endif // HAVE_INTTYPES_H

#ifndef HAVE_STDINT_H
#if __has_include(<stdint.h>)
#define HAVE_STDINT_H 1
#endif // __has_include
#endif // HAVE_STDINT_H

#include <string.h>       // for memcpy()

#ifdef HAVE_INTTYPES_H
// uint16_t might be here; PRId64 too.
#include <inttypes.h>     // gets us PRId64, etc
#endif // HAVE_INTTYPES_H

#ifdef HAVE_STDINT_H
#include <stdint.h>             // to get uint16_t (ISO naming madness)
#endif
#include <sys/types.h>          // our last best hope for uint16_t

// Mostly it's old systems that don't support inttypes.h, so we assume
// they're 32 bit.
#ifndef PRIx64
#define PRIx64 "llx"
#endif
#ifndef SCNx64
#define SCNx64 "llx"
#endif
#ifndef PRId64
#define PRId64 "lld"
#endif
#ifndef SCNd64
#define SCNd64 "lld"
#endif
#ifndef PRIu64
#define PRIu64 "llu"
#endif
#ifndef PRIxPTR
#define PRIxPTR "lx"
#endif

// Also allow for printing of a pthread_t.
#define GPRIuPTHREAD "lu"
#define GPRIxPTHREAD "lx"
