/**
 * Sailfish
 * Copyright (C) 2023 Jozef Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <openssl/ssl.h>
#include <unistd.h>

#include "enc/base64.h"

#include "ui/ui.hpp"

#include "prot/pop3.h"
#include "prot/smtp.h"

#include "utils/sock.h"
#include "utils/utils.h"

int main(int argc, char **argv)
{
	// This section will be commented out before I move this to more appropriate
	// places to prevent spamming the remote server
	/*
	const SSL_METHOD *method;
	SSL_CTX *ssl_ctx;
	SSL *ssl;

	int sockfd = socket_init();

	// init SSL
	OpenSSL_add_all_algorithms();
	if (SSL_library_init() < 0) {
		printf("[!] Couldn't initialize OpenSSL! Exitting...\n");
	} else {
		method = SSLv23_client_method();
		if ((ssl_ctx = SSL_CTX_new(method)) == NULL) {
			printf("[!] Couldn't initialize OpenSSL's context! Exitting...\n");
		} else {
			SSL_CTX_set_options(ssl_ctx, SSL_OP_NO_SSLv2);
			ssl = SSL_new(ssl_ctx);
			SSL_set_fd(ssl, sockfd);
		}
	}

	if (SSL_connect(ssl) != 1) {
		// lol too bad
		printf("[!] Couldn't create SSL session! Exitting...");
		exit(0);
	}

	pop3_connect(ssl);

	pop3_quit(ssl);

	SSL_shutdown(ssl);
	close(sockfd);*/

	ui_init(argc, argv);

	return 0;
}