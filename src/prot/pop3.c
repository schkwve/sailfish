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

#include "../enc/base64.h"
#include "../utils/login.h"
#include "../utils/utils.h"

#include "../utils/login.h"

#include "pop3.h"

void pop3_connect(SSL *ssl)
{
	char *buf[MAX_BUFSIZE];

	recv_verify(&ssl, "+OK");

	sprintf(buf, "user %s\r\n", LOGIN_USERNAME);
	send_verify(&ssl, buf, "+OK");
	sprintf(buf, "pass %s\r\n", LOGIN_PASS);
	send_verify(&ssl, buf, "+OK");
}

void pop3_quit(SSL *ssl)
{
	char *buf[MAX_BUFSIZE];

	sprintf(buf, "quit\r\n");
	data_send(&ssl, buf);
}