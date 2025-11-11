#pragma once

#ifndef NET_TYPES

#include "includes.h"

#pragma pack(1)

// Type definitions
typedef char* string;
typedef int socket_t;
typedef struct sockaddr_in sockAddrIn;
typedef struct sockaddr sockAddr;

enum ConnType {
	UNKNOWN = 0,
	Server = 1,
	Client = 2
};

typedef enum ConnType ConnType_t;

struct socketParams {
	socket_t fd;

	uint32_t Ip; // Stored in local endianness
	uint16_t port; // Port to use, in local endianness

	sockAddrIn socketAddress;
	socklen_t socketLength;
};

typedef struct socketParams socketParams_t;

#define SOCKETPARAMS_SIZE sizeof(socketParams_t)

#pragma pack()
#endif