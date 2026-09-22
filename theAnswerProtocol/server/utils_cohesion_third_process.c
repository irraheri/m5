#include "server.h"
#include "utils.h"

t_dir	define_dir(void)
{
	t_dir	result;

	strcpy(result.dirs[0], "north");
	strcpy(result.dirs[1], "south");
	strcpy(result.dirs[2], "left");
	strcpy(result.dirs[3], "right");
	return (result);
}

void	look_c_add_exits(t_command *test, t_room room)
{
	int		n;
	int		i;
	t_dir	directions;

	directions = define_dir();
	i = 0;
	n = 0;
	while (i < 4)
	{
		if (strcmp(room.exits.ids[i], "none"))
		{
			if (n != 0)
				strcat(test->message, ", ");
			strcat(test->message, "\"");
			strcat(test->message, directions.dirs[i]);
			strcat(test->message, "\": \"");
			strcat(test->message, room.exits.ids[i]);
			strcat(test->message, "\"");
			n++;
		}
		i++;
	}
}

void	look_c_add_players(t_command *test, t_room room,
		t_client_manager *g_client_manager)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < room.players.len)
	{
		j = 0;
		while (j < g_client_manager->number_of_player)
		{
			if (g_client_manager->players[j].fd == atoi(room.players.ids[i]))
			{
				if (k != 0)
					strcat(test->message, ", ");
				strcat(test->message, "\"");
				strcat(test->message, g_client_manager->players[j].name);
				strcat(test->message, "\"");
				k++;
			}
			j++;
		}
		i++;
	}
}

void	look_c_add_items(t_command *test, t_room room)
{
	int	i;

	i = 0;
	while (i < room.items.len)
	{
		if (i != 0)
			strcat(test->message, ", ");
		strcat(test->message, "\"");
		strcat(test->message, room.items.ids[i]);
		strcat(test->message, "\"");
		i++;
	}
}

void	look_c_add_npcs(t_command *test, t_room room)
{
	int	i;

	i = 0;
	while (i < room.npcs.len)
	{
		if (i != 0)
			strcat(test->message, ", ");
		strcat(test->message, "\"");
		strcat(test->message, room.npcs.ids[i]);
		strcat(test->message, "\"");
		i++;
	}
}
