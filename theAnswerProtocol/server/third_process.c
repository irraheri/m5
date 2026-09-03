#include "server.h"

t_signal	third_process(t_command test, int client_fd)
{
	t_signal	result;

	result.number_of_them = 1;
	strcpy(result.message, "MESSAGE OF WHEN ITS OK\n");
	result.all_fd[0] = client_fd;
	return (result);
}
