#pragma once

#ifndef COMMON_CONFIG

#include "includes.h"
#include "endianness.h"

#define IS_DIGIT(CHAR) (('0' <= CHAR) && (CHAR <= '9'))

#pragma pack(1)
typedef struct sockaddr_in sockAddrIn;

typedef struct Config {
	Endianness_t endianness;
	uint32_t ip;
	uint16_t port;
} Config;

#define CONFIG_SIZE sizeof(Config)

#pragma pack()

extern const Config ERR_CONF;

bool fileExists(char* filename);
Config createConfig(uint8_t ip[4], uint16_t port);
Config readConfig(char* filename);
void writeConfig(char* filename, Config config);

sockAddrIn configToSockAddr(Config config);

#define COMMON_CONFIG
#endif
