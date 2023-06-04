#include <unistd.h>

#include "utils/sock.h"
#include "utils/utils.h"

int main(int argc, char **argv)
{
	int sock = socket_init();

	close(sock);

	return 0;
}