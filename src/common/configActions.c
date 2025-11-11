#include "configActions.h"

#include "endianness.h"
#include <sys/stat.h>

bool fileExists(char* filename) {
	struct stat buffer;

	return stat(filename, &buffer) == 0;
}

Config createConfig(uint8_t ip[4], uint16_t port) {
	detectEndian();
	Config output = {sysEndianness, 0, port};

	output.server_ip = *(uint32_t*)ip;

	return output;
}

Config readConfig(char* filename) {
	detectEndian();
	Config output = {0, 0, 0};

	FILE* fp = fopen(filename, "r");

	fread(&output, CONFIG_SIZE, 1, fp);
	fclose(fp);

	if (output.endianness != sysEndianness) {
		swapEndianness(&output.server_ip, 4);
		swapEndianness(&output.server_port, 2);
	}

	return output;
}

void writeConfig(char* filename, Config config) {
	FILE* fp = fopen(filename, "w");

	fwrite(&config, CONFIG_SIZE, 1, fp);
	fclose(fp);
}

static uint8_t* parseIpV4(char* ipString, int8_t delimiters[5]) {
	static uint8_t octets[4] = {0};
	char octetStr[4];
	memset(octetStr, '\0', sizeof(octetStr));

	for (uint8_t octet = 0; octet < 4; octet++) {
		int8_t before, after;

		before = delimiters[octet];
		after = delimiters[octet + 1];

		ptr src = &ipString[before + 1];

		strncpy(octetStr, src, after - before - 1);
		int val = atoi(octetStr);

		if ((0 <= val) && (val < 256)) {
			octets[octet] = (uint8_t)val;
		} else {
			fprintf(stderr, "La configuration fournie ne passe pas le dernier test de formatage de l'adresse IP !\n");
			exit(EXIT_FAILURE);
		}

		memset(octetStr, '\0', sizeof(octetStr));
	}

	return octets;
};

Config parseConfig(char* ipString, char* portString) {
	Config output = ERR_CONF;

	uint8_t ip[4] = {0};
	int8_t delimiters[5] = {0};

	size_t lenIp, lenPort, octetCount;
	bool continueFunction = true;

	lenIp = strnlen(ipString, 16);
	lenPort = strnlen(portString, 6);

	continueFunction = ((7 <= lenIp) && (lenIp <= 15)) && ((0 < lenPort) && (lenPort <= 5));

	delimiters[0] = -1;
	delimiters[4] = lenIp;

	if (!continueFunction) {
		fprintf(stderr, "La configuration fournie ne passe pas le premier test de formatage de l'IP et/ou du port !\n");
		exit(EXIT_FAILURE);
	}

	octetCount = 1;
	uint8_t i;
	uint8_t nDelim = 1;
	char c;

	for (i = 0; i < lenIp; i++) {
		c = ipString[i];
		octetCount += c == '.';

		if ((c != '.') && (!IS_DIGIT(c) || (octetCount > 4))) {
			continueFunction = false;
			break;
		} else if ((c == '.') && (nDelim < 4)) {
			delimiters[nDelim++] = i;
		}
	}

	continueFunction &= (octetCount == 4);

	if (!continueFunction) {
		fprintf(stderr, "La configuration fournie ne passe pas le second test de formatage de l'IP !\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < lenPort; i++) {
		c = portString[i];

		if (c != 0 && !IS_DIGIT(c)) {
			continueFunction = false;
			break;
		}
	}

	if (!continueFunction) {
		fprintf(stderr, "La configuration fournie ne passe pas le second test de formatage du port !\n");
		exit(EXIT_FAILURE);
	}

	memcpy(ip, parseIpV4(ipString, delimiters), sizeof(ip));

	int portVal = atoi(portString);

	if ((0 < portVal) && (portVal <= 0xFFFF)) {
		output.server_port = (uint16_t)portVal;
	} else {
		continueFunction = false;
		fprintf(stderr, "La configuration fournie ne passe pas le dernier test de formatage du port !\n");
		exit(EXIT_FAILURE);
	}

	output.server_ip = *(uint32_t*)ip;
	output.endianness = getEndian();

	return output;
}

socketParams_t configToParams(Config config) {
	detectEndian();

	socketParams_t output;

	uint32_t ip = config.server_ip;
	uint16_t port = config.server_port;

	//toBigEndian(&ip, 4);
	toBigEndian(&port, 2);

	output.connType = UNKNOWN;
	sockAddrIn* socketAddress = &output.socketAddress;

	socketAddress->sin_addr.s_addr = ip;
	socketAddress->sin_port = port;
	socketAddress->sin_family = AF_INET;

	output.socketLength = sizeof(output.socketAddress);

	return output;
}
