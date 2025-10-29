#include "config.h"

#include "endianness.h"
#include <sys/stat.h>

#ifdef COMMON_CONFIG

bool fileExists(char* filename) {
	struct stat buffer;

	return stat(filename, &buffer) == 0;
}

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

void writeConfig(char* filename, Config config) {
	FILE* fp = fopen(filename, "w");

	fwrite(&config, CONFIG_SIZE, 1, fp);
	fclose(fp);
}

sockAddrIn configToSockAddr(Config config) {
	detectEndian();

	sockAddrIn output;

	output.sin_addr.s_addr = config.ip;
	output.sin_port = config.port;
	output.sin_family = AF_INET;

	toBigEndian(&output.sin_addr.s_addr, 4);
	toBigEndian(&output.sin_port, 2);

	return output;
}

#endif