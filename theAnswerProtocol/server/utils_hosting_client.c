#include "server.h"

void	add_player(int client_fd, t_client_manager *manager, t_world *world)
{
	int		i;
	char	client_fd_char[4];

	i = 0;
	while (i < MAX_PLAYER)
	{
		if (manager->players[i].status == 0)
		{
			manager->players[i].fd = client_fd;
			manager->players[i].status = 1;
			snprintf(
				world->rooms.rooms[0].players.ids[
				world->rooms.rooms[0].players.len],
				sizeof(world->rooms.rooms[0].players.ids[
					world->rooms.rooms[0].players.len]),
				"%d", client_fd);
			world->rooms.rooms[0].players.len += 1;
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
			strcpy(manager->players[i].name, "UNAUTHENTICATED");
			manager->players[i].items.len = 0;
			manager->players[i].quests.len = 0;
			manager->players[i].hp = 100;
			manager->players[i].max_hp = 100;
			manager->players[i].attack = 10;
			strcpy(manager->players[i].status_hp, "healthy");
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

void	remove_player_in_world(int client_fd, t_world *world)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < world->rooms.len)
	{
		j = 0;
		while (j < world->rooms.rooms[i].players.len)
		{
			if (client_fd == atoi(world->rooms.rooms[i].players.ids[j]))
			{
				while (j < world->rooms.rooms[i].players.len - 1)
				{
					strcpy(world->rooms.rooms[i].players.ids[j],
						world->rooms.rooms[i].players.ids[j + 1]);
					j++;
				}
				world->rooms.rooms[i].players.len--;
				return ;
			}
			j++;
		}
		i++;
	}
}
