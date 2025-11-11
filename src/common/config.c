#include "config.h"

#include "endianness.h"

#ifdef COMMON_CONFIG

const Config ERR_CONF = {
	.server_ip = 0xFFFFFFFF,
	.server_port = 0x0000,
	.endianness = 0xFF
};

#endif