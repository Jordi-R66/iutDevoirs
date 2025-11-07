#include "common.h"


int main(int argc, char** argv) {
	detectEndian();

	Config config = parseConfig("246.176.156.57", "5754");

	printf("It's all damn right! PORT : %hu\n", config.port);

	return 0;
}
