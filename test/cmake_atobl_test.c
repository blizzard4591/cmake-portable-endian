#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

/* Necessary for some systems to expose functions */
#if !(defined(_WIN16) || defined(_WIN32) || defined(_WIN64))
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

int main (int argc, char** argv) {
	uint32_t var32bit;
	
	uint32_t var32bitResult;
	
	var32bit = 0x76543210L;
	
	var32bitResult = htonl(var32bit);
	var32bitResult = ntohl(var32bit);
	
	return 0;
}
