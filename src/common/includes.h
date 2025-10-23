#pragma once

#ifndef COMMON_INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef _WIN32
	#error "Windows n'est pas supporté pour le moment"
#else
	#include <netinet/in.h>
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
#endif

#define COMMON_INCLUDES
#endif
