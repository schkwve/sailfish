#include <openssl/ssl.h>

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void send_verify(SSL **ssl, char *buf, char *expected)
{
#ifdef DEBUG
	printf("[Client -> Server]: %s", buf);
#endif

	// set and zero out buffer
	SSL_write(*ssl, buf, strlen(buf));
	memset(buf, 0, MAX_BUFSIZE);

	// receive data back and compare to `expected`.
	SSL_read(*ssl, buf, MAX_BUFSIZE);
#ifdef DEBUG
	printf("[Server -> Client]: %s", buf);
#endif
	if (strncmp(buf, expected, strlen(expected)) != 0) {
		printf("[!] Expected value: %s | Got: %s\n", expected, buf);
	}
}

void recv_verify(SSL **ssl, char *expected)
{
	char *buf[MAX_BUFSIZE];

	// receive data back and compare to `expected`.
	SSL_read(*ssl, buf, MAX_BUFSIZE);
#ifdef DEBUG
	printf("[Server -> Client]: %s", buf);
#endif
	if (strncmp(buf, expected, strlen(expected)) != 0) {
		printf("[!] Expected value: %s | Got: %s\n", expected, buf);
	}
}

void data_send(SSL **ssl, char *buf)
{
#ifdef DEBUG
	printf("[Client -> Server]: %s", buf);
#endif

	// set and zero out buffer
	SSL_write(*ssl, buf, strlen(buf));
	memset(buf, 0, MAX_BUFSIZE);
}

char *data_recv(SSL **ssl)
{
	char *buf[MAX_BUFSIZE];

	// receive data back and compare to `expected`.
	SSL_read(*ssl, buf, MAX_BUFSIZE);
#ifdef DEBUG
	printf("[Server -> Client]: %s", buf);
#endif

	return buf;
}