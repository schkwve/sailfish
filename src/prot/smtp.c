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

#include "smtp.h"

#include "../utils/utils.h"

void smtp_auth(int sockfd)
{
	char buf[MAX_BUFSIZE];
	char auth_method[MAX_BUFSIZE];

	memset(buf, 0, sizeof(buf));
	read(sockfd, buf, sizeof(buf));

	// Here we expect to get code 220.
	if (strncmp(buf, "220", 3) != 0) {
		printf("[!] Remote server didn't send code 220! Exitting.\n");
		exit(0);
	}

	// We can now send EHLO.
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "EHLO\n");
	write(sockfd, buf, sizeof(buf));

	memset(buf, 0, sizeof(buf));
	read(sockfd, buf, sizeof(buf));

	strncpy(auth_method, parse_ehlo(buf), sizeof(auth_method));
	printf("[*] Selected authentication method: %s\n", auth_method);
}

char *parse_ehlo(const char *response)
{
	char *token[128];
	char *tmp = response;
	char *res[16];
	int i = 0;
	int j;

	while ((token[i] = strtok_r(tmp, " ", &tmp)))
		i++;
	
	for (j = 0; j < i; j++) {
		if (strncmp(token[j], "CRAM-MD5", 9) == 0) {
			snprintf(res, 9, "%s", token[j]);
			break;
		}
		if (strncmp(token[j], "LOGIN", 6) == 0) {
			snprintf(res, 6, "%s", token[j]);
			continue;
		}
		if (strncmp(token[j], "PLAIN", 6) == 0) {
			snprintf(res, 6, "%s", token[j]);
			continue;
		}
	}

	return res;
}