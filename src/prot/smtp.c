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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

#include "smtp.h"
#include "../enc/base64.h"
#include "../utils/utils.h"

#include "../utils/login.h"

void smtp_auth(int sockfd)
{
	char buf[MAX_BUFSIZE];
	char auth_method[MAX_BUFSIZE];

	BIO *obj_bio = NULL;
	BIO *obj_out = NULL;
	const SSL_METHOD *method;
	SSL_CTX *ssl_ctx;
	SSL *ssl;

	int read_sz = 0;

	OpenSSL_add_all_algorithms();
	ERR_load_BIO_strings();
	ERR_load_crypto_strings();
	SSL_load_error_strings();

	obj_bio = BIO_new(BIO_s_file());
	obj_out = BIO_new_fp(stdout, BIO_NOCLOSE);

	if (SSL_library_init() < 0) {
		BIO_printf(obj_out, "OpenSSL couldn't be initialized");
	} else {
		method = SSLv23_client_method();
		if ((ssl_ctx = SSL_CTX_new(method)) == NULL) {
			BIO_printf(obj_out, "OpenSSL context couldn't be initialized");
		} else {
			SSL_CTX_set_options(ssl_ctx, SSL_OP_NO_SSLv2);
			ssl = SSL_new(ssl_ctx);
			SSL_set_fd(ssl, sockfd);
		}
	}

	if (SSL_connect(ssl) != 1) {
		// TODO: Try to not use SSL or smth idk
		printf("[!] Couldn't create SSL session! Exitting...");
		exit(0);
	}

	memset(buf, 0, sizeof(buf));
	read_sz = SSL_read(ssl, buf, sizeof(buf));

	// Here we expect to get code 220.
	if (strncmp(buf, "220", 3) != 0) {
		printf("[!] Remote server didn't send code 220! Got response: %s\n", buf);
		exit(0);
	}

	// We can now send EHLO.
	memset(buf, 0, sizeof(buf));
	strcat(buf, "EHLO localhost\r\n");
	SSL_write(ssl, buf, strlen(buf));

	memset(buf, 0, sizeof(buf));
	read_sz = SSL_read(ssl, buf, sizeof(buf));

	printf("%s\n", buf);

	smtp_login(&ssl, buf);
}

void smtp_login(SSL **ssl, const char *response)
{
	char *token[128];
	char *buf[MAX_BUFSIZE];
	char *tmp = response;
	char *res[16];
	int i = 0;
	int j;

	char *login_challenge[MAX_BUFSIZE];

	while ((token[i] = strtok_r(tmp, " ", &tmp)))
		i++;
	
	/// FIXME: Self-explanatory.
	for (j = 0; j < i; j++) {
		if (strncmp(token[j], "XOAUTH2", 8) == 0) {
			snprintf(res, 9, "%s", token[j]);
			break;
		}
		/*if (strncmp(token[j], "CRAM-MD5", 9) == 0) {
			snprintf(res, 9, "%s", token[j]);
			continue;
		}
		if (strncmp(token[j], "LOGIN", 6) == 0) {
			snprintf(res, 6, "%s", token[j]);
			continue;
		}
		if (strncmp(token[j], "PLAIN", 6) == 0) {
			snprintf(res, 6, "%s", token[j]);
			continue;
		}*/
	}

	if (strncmp(res, "XOAUTH2", 8) == 0) {
		sprintf(login_challenge, "user=%s\001auth=Bearer %s\001\001", XOAUTH2_USER, XOAUTH2_ACCESS_TOKEN);
		sprintf(buf, "AUTH XOAUTH2 %s\n", base64_encode(login_challenge));
		SSL_write(*ssl, buf, strlen(buf));
		printf("Written: %s\n", buf);

		// lelz
		memset(login_challenge, 0, sizeof(login_challenge));

		SSL_read(*ssl, buf, sizeof(buf));
		printf("%s\n", buf);

		memset(buf, 0, sizeof(buf));
		SSL_write(*ssl, buf, sizeof(buf));

		memset(buf, 0, sizeof(buf));
		SSL_read(*ssl, buf, sizeof(buf));
		printf("%s\n", buf);
	}
}