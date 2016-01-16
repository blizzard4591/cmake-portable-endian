#ifndef ENDIANNESS_TEST_PRINTF_TYPES_H_
#define ENDIANNESS_TEST_PRINTF_TYPES_H_

#include <stddef.h>
#include <stdint.h>

#ifdef ENDIANNESS_CONFIG_TESTCOMPILE_HAVE_INTTYPES_H
#	include <inttypes.h>
#endif

#if !defined(PRIu64)
#	ifdef _MSC_VER
#		define PRIu64 "I64u"
#	else
#		define PRIu64 "llu"
#	endif
#endif /* PRIu64 */

#if !defined(PRIu32)
#	ifdef _MSC_VER
#		define PRIu32 "I32u"
#	else
#		define PRIu32 "lu"
#	endif
#endif /* PRIu32 */

#if !defined(PRIu16)
#	ifdef _MSC_VER
#		define PRIu16 "hu"
#	else
#		define PRIu16 "u"
#	endif
#endif /* PRIu16 */

#define PRINTF_UINT16_T_QUALIFIER PRIu16
#define PRINTF_UINT32_T_QUALIFIER PRIu32
#define PRINTF_UINT64_T_QUALIFIER PRIu64

/* MSVC version 1800 */
#if defined(_MSC_VER) && (_MSC_VER <= 1800)
#	define PRINTF_SIZE_T_QUALIFIER "Iu"
#elif defined(ENDIANNESS_CONFIG_TESTCOMPILE_NO_ZU_SUPPORT)
#	define PRINTF_SIZE_T_QUALIFIER "u"
#else
#	define PRINTF_SIZE_T_QUALIFIER "zu"
#endif

#endif /* ENDIANNESS_TEST_PRINTF_TYPES_H_ */
