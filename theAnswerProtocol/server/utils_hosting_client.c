#include "server.h"

void	add_player(int client_fd, t_client_manager *manager)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYER)
	{
		if (manager->players[i].status == 0)
		{
			manager->players[i].fd = client_fd;
			manager->players[i].status = 1;
			return ;
		}
		i++;
	}
	log_date();
	printf("EXCEDED MAX_PLAYER (%d)\n", MAX_PLAYER);
	exit(0);
}

void	remove_player(int client_fd, t_client_manager *manager)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYER)
	{
		if (manager->players[i].fd == client_fd)
		{
			manager->players[i].fd = -1;
			manager->players[i].status = 0;
			pthread_mutex_lock(&(manager->mutex));
			manager->number_of_player -= 1;
			pthread_mutex_unlock(&(manager->mutex));
			return ;
		}
		i++;
	}
}

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
