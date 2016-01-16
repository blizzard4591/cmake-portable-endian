#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

#include "printf_types.h"

#ifdef ENDIANNESS_CONFIG_TESTCOMPILE_TRY_MSVC_SYNTAX
#	define __builtin_bswap16(x) _byteswap_ushort((x))
#	define __builtin_bswap32(x) _byteswap_ulong((x))
#	define __builtin_bswap64(x) _byteswap_uint64((x))
#endif

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
	
	var16bitResult = __builtin_bswap16(var16bit);
	
	var32bitResult = __builtin_bswap32(var32bit);
	
	var64bitResult = __builtin_bswap64(var64bit);
	
	/* for preventing unused variable warnings */
	printf("Argc = %i\nArgv[0] = %s\nResult 16bit = %"PRIu16"\nResult 32bit = %"PRIu32"\nResult 64bit = %"PRIu64"\n", argc, argv[0], var16bitResult, var32bitResult, var64bitResult);
	
	return 0;
}
