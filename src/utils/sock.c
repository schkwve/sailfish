#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include "sock.h"
#include "utils.h"

int socket_init()
{
	int sockfd;
	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("[!] Couldn't create socket: %s\n", strerror(errno));
		exit(0);
	}

	printf("[*] Created socket\n");
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	servaddr.sin_port = htons(SERVER_PORT);

	if (connect(sockfd, (sockaddr_t *)&servaddr, sizeof(servaddr)) != 0) {
		printf("[!] Couldn't connect to server: %s\n", strerror(errno));
		exit(0);
	}

	printf("[*] Connected to %s:%d\n", SERVER_IP, SERVER_PORT);

	return sockfd;
}