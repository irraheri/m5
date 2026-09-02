#include "server.h"

int	player_id(int client_fd, t_client_manager gmanager)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYER)
	{
		if (gmanager.players[i].fd == client_fd)
			return (i + 1);
		else
			i++;
	}
	return (0);
}
