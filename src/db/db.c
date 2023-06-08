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

#include <stdlib.h>
#include <stdio.h>

#include <sqlite3.h>

void init_db()
{
	sqlite3* sql_db;
    char *init_query[128];
	sprintf(init_query, "CREATE TABLE accounts(ID INT PRIMARY KEY     NOT NULL, NAME           TEXT    NOT NULL, TYPE          TEXT     NOT NULL, SERVER            TEXT     NOT NULL );");

    int result = 0;
    char* message_err;

    result = sqlite3_open("accounts.db", &sql_db);
    result = sqlite3_exec(sql_db, init_query, NULL, 0, &message_err);
  
    if (result != SQLITE_OK) {
        printf("[!] An error occured while initializing database!\n");
        sqlite3_free(message_err);
    }

    sqlite3_close(sql_db);
}

int add_user(char *name, char *type, char *server)
{
	sqlite3 *sql_db;

	char sql_query[512];
	int result;
	sqlite3_stmt *stmt;
	char *message_err;
	int id;
	
	// no error handling - i like living dangerously
	result = sqlite3_open("accounts.db", &sql_db);
	if (result != SQLITE_OK) {
		printf("[!] An error occured while opening database!\n");
		sqlite3_free(message_err);
		return -1;
	}

	result = sqlite3_prepare_v2(sql_db, "SELECT COUNT(*) FROM accounts;", -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		sqlite3_free(message_err);
		return -2;
	}
	result = sqlite3_step(stmt);
	if (result != SQLITE_ROW) {
		sqlite3_free(message_err);
		return -3;
	}

	id = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);

	printf("[*] Adding user ID=%i...\n", id);
	sprintf(sql_query, "INSERT INTO accounts(ID, NAME, TYPE, SERVER) VALUES (%i, \"%s\", \"%s\", \"%s\");", id, name, type, server);

	result = sqlite3_exec(sql_db, sql_query, NULL, 0, &message_err);
	if (result != SQLITE_OK) {
		printf("[!] An error occured while adding user!\n");
		sqlite3_free(message_err);
		return -4;
	}

	sqlite3_close(sql_db);

	return id;
}

int remove_user(int index)
{
	sqlite3 *sql_db;

	char sql_query[64];
	int result = 0;
	char *message_err;

	sprintf(sql_query, "DELETE FROM accounts WHERE ID = %i;", index);
	printf("[*] Removing user ID=%i...\n", index);

	result = sqlite3_open("accounts.db", &sql_db);
	if (result != SQLITE_OK) {
		printf("[!] An error occured while opening database!\n");
		sqlite3_free(message_err);
	}

	result = sqlite3_exec(sql_db, sql_query, NULL, 0, &message_err);
	if (result != SQLITE_OK) {
		printf("[!] An error occured while removing user!\n");
		sqlite3_free(message_err);
	}

	sprintf(sql_query, "UPDATE accounts SET ID = ID - 1 WHERE ID > %i;", index);
	result = sqlite3_exec(sql_db, sql_query, NULL, 0, &message_err);
	if (result != SQLITE_OK) {
		printf("[!] An error occured while resetting IDs!\n");
		sqlite3_free(message_err);
	}

	sqlite3_close(sql_db);
}