#include "config.h"

#include "endianness.h"

#ifdef COMMON_CONFIG

Config createConfig(uint8_t ip[4], uint16_t port) {
	detectEndian();
	Config output = {sysEndianness, 0, port};

	output.ip = *(uint32_t*)ip;

	return output;
}

Config readConfig(char* filename) {
	detectEndian();
	Config output = {0, 0, 0};

	FILE* fp = fopen(filename, "r");

	fread(&output, CONFIG_SIZE, 1, fp);
	fclose(fp);

	if (output.endianness != sysEndianness) {
		swapEndianness(&output.ip, 4);
		swapEndianness(&output.port, 2);
	}

	return output;
}

#endif