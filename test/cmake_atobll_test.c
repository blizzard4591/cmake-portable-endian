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

#ifdef ENDIANNESS_CONFIG_TESTCOMPILE_HAVE_WINSOCK2_H
#	include <WinSock2.h>
#endif

#ifdef ENDIANNESS_CONFIG_TESTCOMPILE_HAVE_ARPA_INET_H
#	include <arpa/inet.h>
#endif

#ifdef ENDIANNESS_CONFIG_TESTCOMPILE_HAVE_NETINET_IN_H
#	include <netinet/in.h>
#endif

#include "printf_types.h"

int main (int argc, char** argv) {
	uint64_t var64bit;
	uint64_t tmp;
	
	uint64_t var64bitResult;
	
	var64bit = 0x76543210L;
	
	tmp = 0xFEDCBA98L;
	var64bit = var64bit | (tmp << 32);
	
	var64bitResult = htonll(var64bit);
	var64bitResult = ntohll(var64bit);
	
	/* for preventing unused variable warnings */
	printf("Argc = %i\nArgv[0] = %s\nResult 64bit = %"PRIu64"\n", argc, argv[0], var64bitResult);
	
	return 0;
}
