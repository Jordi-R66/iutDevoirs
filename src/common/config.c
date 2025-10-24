#include "config.h"

#include "endianness.h"

#ifdef COMMON_CONFIG

Config createConfig(uint8_t ip[4], uint16_t port) {
	detectEndian();
	Config output = {sysEndianness, 0, port};

	output.ip = *(uint32_t*)ip;

	return output;
}

#endif