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

#ifndef __UTILS_H_
#define __UTILS_H_

#include <stdio.h>
#include <string.h>

#include <openssl/ssl.h>

#define SERVER_IP "77.75.79.90" // pop3.seznam.cz
#define SERVER_PORT 995

// Isn't this more than enough?
#define MAX_BUFSIZE 16384

///
void send_verify(SSL **ssl, char *buf, char *expected);
void recv_verify(SSL **ssl, char *expected);
void data_send(SSL **ssl, char *buf);
char *data_recv(SSL **ssl);

#endif // __UTILS_H_