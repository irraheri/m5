#include "server.h"

void attack_player(t_signal *result, t_command test, int client_fd,
		t_world *g_world)
{
    int i;

    i = -1;
    while (++i < MAX_PLAYER)
    {
        
    }
}

void	attack(t_signal *result, t_command test, int client_fd,
		t_world *g_world)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g_world->rooms.len)
	{
		j = -1;
		while (++j < g_world->rooms.rooms->players.len)
		{
			if (client_fd == atoi(g_world->rooms.rooms->players.ids[j]))
			{
				if (in(test.message, g_world->rooms.rooms->players))
					attack_player(result, test, client_fd, g_world);
				else
					attack_npc(result, test, client_fd, g_world);
			}
		}
	}
}
