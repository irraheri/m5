#include "server.h"

t_signal	cohesion(int client_fd, char *buf)
{
	t_signal	a;

	a.number_of_them = 1;
	a.all_fd[0] = client_fd;
	strcpy(a.message, "merci pour le message!\n");
	return (a);
}
