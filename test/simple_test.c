#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

/* MSVC version 1800 */
#if defined(_MSC_VER) && (_MSC_VER <= 1800)
#define PRINTF_SIZE_T_QUALIFIER "Iu"
#else
#define PRINTF_SIZE_T_QUALIFIER "zu"
#endif

#include "endianness_config.h"

#define ENDIANNESS_TEST_MACRO_COMPARE_RESULT(funcName, convTargetUnion, sourceUnion, cmpUnion, byteCount) do { \
	convTargetUnion.integer_value = funcName(sourceUnion.integer_value); \
	for (i = 0; i < byteCount; ++i) { \
		if (convTargetUnion.char_values[i] != cmpUnion.char_values[i]) { \
			printf("Test on "#funcName" failed at position %" PRINTF_SIZE_T_QUALIFIER ", where it should be 0x%02x but was 0x%02x instead.", i, convTargetUnion.char_values[i], cmpUnion.char_values[i]); \
			return -1; \
		} \
	} \
} while (1 == 0)

int main (int argc, char** argv) {
	/* 0x3210 */
	union Endian_Data_16 data16bitHost;
	union Endian_Data_16 data16bitLittle;
	union Endian_Data_16 data16bitBig;
	
	data16bitHost.integer_value = 12816;
	data16bitLittle.char_values[0] = 0x10;
	data16bitLittle.char_values[1] = 0x32;
	data16bitBig.char_values[0] = 0x32;
	data16bitBig.char_values[1] = 0x10;
	
	/* 0x76543210 */
	union Endian_Data_32 data32bitHost;
	union Endian_Data_32 data32bitLittle;
	union Endian_Data_32 data32bitBig;
	
	data32bitHost.integer_value = 1985229328L;
	data32bitLittle.char_values[0] = 0x10;
	data32bitLittle.char_values[1] = 0x32;
	data32bitLittle.char_values[2] = 0x54;
	data32bitLittle.char_values[3] = 0x76;
	data32bitBig.char_values[0] = 0x76;
	data32bitBig.char_values[1] = 0x54;
	data32bitBig.char_values[2] = 0x32;
	data32bitBig.char_values[3] = 0x10;
	
	/* 0xFEDCBA9876543210 */
	union Endian_Data_64 data64bitHost;
	union Endian_Data_64 data64bitLittle;
	union Endian_Data_64 data64bitBig;
	
	data64bitHost.integer_value = 18364758544493064720ULL;
	data64bitLittle.char_values[0] = 0x10;
	data64bitLittle.char_values[1] = 0x32;
	data64bitLittle.char_values[2] = 0x54;
	data64bitLittle.char_values[3] = 0x76;
	data64bitLittle.char_values[4] = 0x98;
	data64bitLittle.char_values[5] = 0xBA;
	data64bitLittle.char_values[6] = 0xDC;
	data64bitLittle.char_values[7] = 0xFE;
	data64bitBig.char_values[0] = 0xFE;
	data64bitBig.char_values[1] = 0xDC;
	data64bitBig.char_values[2] = 0xBA;
	data64bitBig.char_values[3] = 0x98;
	data64bitBig.char_values[4] = 0x76;
	data64bitBig.char_values[5] = 0x54;
	data64bitBig.char_values[6] = 0x32;
	data64bitBig.char_values[7] = 0x10;
	
	union Endian_Data_16 data16bit;
	union Endian_Data_32 data32bit;
	union Endian_Data_64 data64bit;
	size_t i;
	
	/* htobe16 */
	ENDIANNESS_TEST_MACRO_COMPARE_RESULT(htobe16, data16bit, data16bitHost, data16bitBig, 2);
	
	/* htole16 */
	ENDIANNESS_TEST_MACRO_COMPARE_RESULT(htole16, data16bit, data16bitHost, data16bitLittle, 2);
	
	/* htobe32 */
	ENDIANNESS_TEST_MACRO_COMPARE_RESULT(htobe32, data32bit, data32bitHost, data32bitBig, 4);
	
	/* htole32 */
	ENDIANNESS_TEST_MACRO_COMPARE_RESULT(htole32, data32bit, data32bitHost, data32bitLittle, 4);
	
	/* htobe64 */
	ENDIANNESS_TEST_MACRO_COMPARE_RESULT(htobe64, data64bit, data64bitHost, data64bitBig, 8);
	
	/* htole64 */
	ENDIANNESS_TEST_MACRO_COMPARE_RESULT(htole64, data64bit, data64bitHost, data64bitLittle, 8);

	/* betoh16 */
	ENDIANNESS_TEST_MACRO_COMPARE_RESULT(betoh16, data16bit, data16bitBig, data16bitHost, 2);
	
	/* letoh16 */
	ENDIANNESS_TEST_MACRO_COMPARE_RESULT(letoh16, data16bit, data16bitLittle, data16bitHost, 2);
	
	/* betoh32 */
	ENDIANNESS_TEST_MACRO_COMPARE_RESULT(betoh32, data32bit, data32bitBig, data32bitHost, 4);
	
	/* letoh32 */
	ENDIANNESS_TEST_MACRO_COMPARE_RESULT(letoh32, data32bit, data32bitLittle, data32bitHost, 4);
	
	/* betoh64 */
	ENDIANNESS_TEST_MACRO_COMPARE_RESULT(betoh64, data64bit, data64bitBig, data64bitHost, 8);
	
	/* letoh64 */
	ENDIANNESS_TEST_MACRO_COMPARE_RESULT(letoh64, data64bit, data64bitLittle, data64bitHost, 8);
	
	return 1;
}
