#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

/* Necessary for some systems to expose functions */
#if !(defined(_WIN16) || defined(_WIN32) || defined(_WIN64))
#	ifndef __USE_BSD
#		define __USE_BSD
#	endif
#	ifndef _BSD_SOURCE
#		define _BSD_SOURCE
#	endif
#	ifndef _SVID_SOURCE
#		define _SVID_SOURCE
#	endif
#	ifndef _DEFAULT_SOURCE
#		define _DEFAULT_SOURCE
#	endif
#endif

#ifdef ENDIANNESS_CONFIG_TESTCOMPILE_HAVE_ENDIAN_H
#	include <endian.h>
#endif

#ifdef ENDIANNESS_CONFIG_TESTCOMPILE_HAVE_SYS_ENDIAN_H
#	include <sys/endian.h>
#endif

#ifdef ENDIANNESS_CONFIG_TESTCOMPILE_TRY_OPENBSD_SYNTAX
#	define le16toh(x) letoh16((x))
#	define le32toh(x) letoh32((x))
#	define le64toh(x) letoh64((x))
#endif

#include "printf_types.h"

int main (int argc, char** argv) {
	uint16_t var16bit;
	uint32_t var32bit;
	uint64_t var64bit;
	uint64_t tmp;
	
	uint16_t var16bitResult;
	uint32_t var32bitResult;
	uint64_t var64bitResult;
	
	var16bit = 0x3210;
	var32bit = 0x76543210L;
	var64bit = 0x76543210L;
	
	tmp = 0xFEDCBA98L;
	var64bit = var64bit | (tmp << 32);
	
	var16bitResult = le16toh(var16bit);
	var16bitResult = htobe16(var16bit);
	
	var32bitResult = le32toh(var32bit);
	var32bitResult = htobe32(var32bit);
	
	var64bitResult = le64toh(var64bit);
	var64bitResult = htobe64(var64bit);

	/* for preventing unused variable warnings */
	printf("Argc = %i\nArgv[0] = %s\nResult 16bit = %"PRIu16"\nResult 32bit = %"PRIu32"\nResult 64bit = %"PRIu64"\n", argc, argv[0], var16bitResult, var32bitResult, var64bitResult);

	return 0;
}
