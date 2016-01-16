#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "printf_types.h"

/* Test local endianness.
 *
 */

union Endian_Data_16 {
	uint16_t integer_value;
	unsigned char char_values[2];
};
 
union Endian_Data_32 {
	uint32_t integer_value;
	unsigned char char_values[4];
};

union Endian_Data_64 {
	uint64_t integer_value;
	unsigned char char_values[8];
};

#define RETURNVAR_SANITY_TEST_FAILED 0
#define RETURNVAR_SANITY_TEST_OK 1
 
#define RETURNVAR_LITTLE_ENDIAN 1
#define RETURNVAR_BIG_ENDIAN 2
#define RETURNVAR_MIXED_ENDIAN 3

#define ENDIANNESS_MACRO_PRIMITVE_TYPE_FROM_BITS(bits) uint ## bits ## _t

#define ENDIANNESS_MACRO_PRIMITVE_TYPE_MAX_MACRO_FROM_BITS(bits) UINT ## bits ## _MAX

#define ENDIANNESS_MACRO_PRIMITVE_TYPE_PRINTF_MACRO_FROM_BITS(bits) PRINTF_UINT ## bits ## _T_QUALIFIER

#define ENDIANNESS_MACRO_SANITY_TEST(bits, returnvar) \
	/* Test whether the given uint type of bits is really bits long */ \
	union Endian_Data_##bits endian_data; \
	size_t size_of_endian_data; \
	size_of_endian_data = sizeof(union Endian_Data_##bits); \
	endian_data.integer_value = ENDIANNESS_MACRO_PRIMITVE_TYPE_MAX_MACRO_FROM_BITS(bits); \
\
	returnvar = (RETURNVAR_SANITY_TEST_OK); \
	size_t i; \
	for (i = 0; i < size_of_endian_data; ++i) { \
		unsigned char value; \
		value = endian_data.char_values[i]; \
		if (value != 0xFF) { \
			printf("Error: Sanity test for "#bits"-bits failed for Byte 0x%02x at position %" PRINTF_SIZE_T_QUALIFIER "!\n", value, i); \
			returnvar = (RETURNVAR_SANITY_TEST_FAILED); \
		} \
	}

#define ENDIANNESS_MACRO_PERFORM_TEST(bits, returnvar) \
	/* Test endianness of architecture */ \
	union Endian_Data_##bits endian_data; \
	size_t size_of_endian_data; \
	size_of_endian_data = sizeof(union Endian_Data_##bits); \
\
	endian_data.integer_value = 0; \
	ENDIANNESS_MACRO_PRIMITVE_TYPE_FROM_BITS(bits) multiplication_value; \
	multiplication_value = 1; \
	ENDIANNESS_MACRO_PRIMITVE_TYPE_FROM_BITS(bits) i; \
	/* Create a constant of the form 0x03020100 */ \
	for (i = 0; i < size_of_endian_data; ++i) { \
		endian_data.integer_value += i * multiplication_value; \
		multiplication_value *= 256; \
	} \
	printf("// Constant for "#bits"-bits is %" ENDIANNESS_MACRO_PRIMITVE_TYPE_PRINTF_MACRO_FROM_BITS(bits) ".\n", endian_data.integer_value); \
 \
	char position_LSB_plus[sizeof(union Endian_Data_##bits)]; \
	/* Initialize to "invalid" */ \
	for (i = 0; i < size_of_endian_data; ++i) { \
		position_LSB_plus[i] = -1; \
		printf("// Byte %" ENDIANNESS_MACRO_PRIMITVE_TYPE_PRINTF_MACRO_FROM_BITS(bits) " in "#bits"-bits constant is 0x%02x.\n", i, endian_data.char_values[i]); \
	} \
 \
	int is_little_endian; \
	is_little_endian = 0; \
	int is_big_endian; \
	is_big_endian = 0; \
 \
	for (i = 0; i < size_of_endian_data; ++i) { \
		unsigned char value; \
		value = endian_data.char_values[i]; \
		if (value < size_of_endian_data) { \
			position_LSB_plus[value] = (char)i; \
		} else { \
			printf("Error: Unknown Byte 0x%02x at position %" ENDIANNESS_MACRO_PRIMITVE_TYPE_PRINTF_MACRO_FROM_BITS(bits) "!\n", value, i); \
			return 1; \
		} \
	} \
 \
	for (i = 0; i < size_of_endian_data; ++i) { \
		if (position_LSB_plus[i] == -1) { \
			printf("Error: Did not find Index for LSB+%" ENDIANNESS_MACRO_PRIMITVE_TYPE_PRINTF_MACRO_FROM_BITS(bits) "?!\n", i); \
			return 2; \
		} \
	} \
 \
	for (i = 0; i < size_of_endian_data; ++i) { \
		printf("#define ENDIANNESS_%" PRINTF_SIZE_T_QUALIFIER "_BYTE_TYPE_LSB_PLUS_%" ENDIANNESS_MACRO_PRIMITVE_TYPE_PRINTF_MACRO_FROM_BITS(bits) "_INDEX %i\n", size_of_endian_data, i, position_LSB_plus[i]); \
	} \
 \
	/* Is it little endian? */ \
	is_little_endian = 1; \
	if (position_LSB_plus[0] != 0) { \
		is_little_endian = 0; \
	} else { \
		for (i = 1; i < size_of_endian_data; ++i) { \
			if (position_LSB_plus[i - 1] != (position_LSB_plus[i] - 1)) { \
				is_little_endian = 0; \
				break; \
			} \
		} \
	} \
 \
	/* Is it big endian? */ \
	is_big_endian = 1; \
	if (position_LSB_plus[0] != (char)(size_of_endian_data - 1)) { \
		is_big_endian = 0; \
	} else { \
		for (i = 1; i < size_of_endian_data; ++i) { \
			if (position_LSB_plus[i - 1] != (char)(position_LSB_plus[i] + 1)) { \
				is_big_endian = 0; \
				break; \
			} \
		} \
	} \
 \
	if (is_little_endian && is_big_endian) { \
		printf("Error: Detected both big and little endian. This should not happen.\n"); \
		return 3; \
	} else if (is_little_endian) { \
		returnvar = RETURNVAR_LITTLE_ENDIAN; \
	} else if (is_big_endian) { \
		returnvar = RETURNVAR_BIG_ENDIAN; \
	} else { \
		returnvar = RETURNVAR_MIXED_ENDIAN; \
	} \
 \
	printf("#define ENDIANNESS_%" PRINTF_SIZE_T_QUALIFIER "_BYTE_TYPE_IS_LITTLE_ENDIAN %i\n", size_of_endian_data, is_little_endian); \
	printf("#define ENDIANNESS_%" PRINTF_SIZE_T_QUALIFIER "_BYTE_TYPE_IS_BIG_ENDIAN %i\n", size_of_endian_data, is_big_endian);
 
int main(int argc, char* argv[]) {
	int sanity_test_16bit_result;
	int sanity_test_32bit_result;
	int sanity_test_64bit_result;
	
	sanity_test_16bit_result = 0;
	sanity_test_32bit_result = 0;
	sanity_test_64bit_result = 0;
	{
	ENDIANNESS_MACRO_SANITY_TEST(16, sanity_test_16bit_result);
	}
	{
	ENDIANNESS_MACRO_SANITY_TEST(32, sanity_test_32bit_result);
	}
	{
	ENDIANNESS_MACRO_SANITY_TEST(64, sanity_test_64bit_result);
	}
	
	if (sanity_test_16bit_result != (RETURNVAR_SANITY_TEST_OK)) {
		printf("Error: Sanity Test on uint16_t failed. Unsupported architecture.\n");
		return 5;
	} else if (sanity_test_32bit_result != (RETURNVAR_SANITY_TEST_OK)) {
		printf("Error: Sanity Test on uint32_t failed. Unsupported architecture.\n");
		return 5;
	} else if (sanity_test_64bit_result != (RETURNVAR_SANITY_TEST_OK)) {
		printf("Error: Sanity Test on uint64_t failed. Unsupported architecture.\n");
		return 5;
	}

	int test_16bit_result;
	int test_32bit_result;
	int test_64bit_result;
	
	test_16bit_result = 0;
	test_32bit_result = 0;
	test_64bit_result = 0;
	{
	ENDIANNESS_MACRO_PERFORM_TEST(16, test_16bit_result);
	}
	{
	ENDIANNESS_MACRO_PERFORM_TEST(32, test_32bit_result);
	}
	{
	ENDIANNESS_MACRO_PERFORM_TEST(64, test_64bit_result);
	}
	
	if ((test_16bit_result == test_32bit_result) && (test_32bit_result == test_64bit_result)) {
		printf("// A value for identifying endiannes\n");
		printf("#define ENDIANNESS_VAL_LITTLE_ENDIAN 1\n");
		printf("#define ENDIANNESS_VAL_BIG_ENDIAN 2\n");
		printf("#define ENDIANNESS_VAL_MIXED_ENDIAN 3\n");
		if (test_16bit_result == RETURNVAR_LITTLE_ENDIAN) {
			printf("#define ENDIANNESS_CONFIG_ENDIAN_TYPE ENDIANNESS_VAL_LITTLE_ENDIAN\n");
		} else if (test_16bit_result == RETURNVAR_BIG_ENDIAN) {
			printf("#define ENDIANNESS_CONFIG_ENDIAN_TYPE ENDIANNESS_VAL_BIG_ENDIAN\n");
		} else {
			printf("#define ENDIANNESS_CONFIG_ENDIAN_TYPE ENDIANNESS_VAL_MIXED_ENDIAN\n");
		}
	} else {
		printf("Error: 16bit, 32bit and 64bit Endian is NOT equivalent. Unknown/unsupported architecture.\n"); /* This should _not_ exist. */
		return 4;
	}
	
	return 0;
}
