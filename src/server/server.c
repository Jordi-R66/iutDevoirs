#include "common.h"

/**
 * @brief Prepares the socket and binds it to the correct port and address.
 * 
 * @param Config the configuration of the server (ip and port in local endianness)
 * @return socket_t 
 */
socketParams_t prepareSocket(Config config) {
	socketParams_t output = configToParams(config);

	socket_t socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1) {
		fprintf(stderr, "Socket creation failed\n");
		perror("Details ");
		exit(EXIT_FAILURE);
	}

	output.fd = socket_fd;

	int bind_ret_code = bind(output.fd, (const sockAddr*)&output.socketAddress, output.socketLength);

	if (bind_ret_code < 0) {
		fprintf(stderr, "Couldn't bind socket\n");
		perror("Details ");
		shutdown(output.fd, SHUT_RDWR);
		close(output.fd);
		exit(EXIT_FAILURE);
	}

	return output;
}

int main(int argc, char** argv) {
	detectEndian();

	printf("Endianness detected!!\n");
	Config config = parseConfig("10.8.0.6", "5754");

	socketParams_t socketparams = prepareSocket(config);

	socket_t socket_fd = socketparams.fd;

	int listen_rt = listen(socket_fd, 1);
	int connected_fd = accept(socket_fd, (struct sockaddr*)&socketparams, &socketparams.socketLength);

	char buff[256];

	ssize_t received = recv(connected_fd, buff, 256, 0);

	printf("%s\n", buff);

	close(connected_fd);
	close(socket_fd);

	return 0;
}
