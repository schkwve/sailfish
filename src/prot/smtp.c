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

#include "smtp.h"

void smtp_auth(SSL *ssl)
{
	char *buf[MAX_BUFSIZE];

	recv_verify(&ssl, "220");

	// We can now send EHLO.
	// FIXME: set own domain name
	sprintf(buf, "EHLO localhost\r\n");
	send_verify(&ssl, buf, "250");

	sprintf(buf, "AUTH LOGIN\r\n");
	send_verify(&ssl, buf, "334 VXNlcm5hbWU6"); // 334 Username:
	sprintf(buf, "%s\r\n", base64_encode(LOGIN_USERNAME));
	send_verify(&ssl, buf, "334 UGFzc3dvcmQ6"); // 334 Password:
	sprintf(buf, "%s\r\n", base64_encode(LOGIN_PASS));
	send_verify(&ssl, buf, "235"); // Authentication successful
}

void smtp_quit(SSL *ssl)
{
	char *buf[MAX_BUFSIZE];
	sprintf(buf, "QUIT\r\n");
	data_send(&ssl, buf);
}