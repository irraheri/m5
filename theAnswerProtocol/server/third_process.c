#include "third_process.h"

void	look_c(t_command *test, t_room room, t_client_manager *g_manager)
{
	strcpy(test->message, "OK ");
	strcat(test->message, "{ \"room\": {");
	strcat(test->message, " \"id\": \"");
	strcat(test->message, room.id);
	strcat(test->message, "\", \"name\": \"");
	strcat(test->message, room.name);
	strcat(test->message, "\", \"description\": \"");
	strcat(test->message, room.description);
	strcat(test->message, "\", \"exits\": {");
	look_c_add_exits(test, room);
	strcat(test->message, "}}");
	strcat(test->message, ", \"players\": [");
	look_c_add_players(test, room, g_manager);
	strcat(test->message, "], \"items\": [");
	look_c_add_items(test, room);
	strcat(test->message, "], \"npcs\": [");
	look_c_add_npcs(test, room);
	strcat(test->message, "] }\n");
}

void	look_state_proc(t_command *test, int client_fd, t_world *g_world,
		t_client_manager *g_manager)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_world->rooms.len)
	{
		j = 0;
		while (j < g_world->rooms.rooms[i].players.len)
		{
			if (client_fd == atoi(g_world->rooms.rooms[i].players.ids[j]))
			{
				look_c(test, g_world->rooms.rooms[i], g_manager);
				break ;
			}
			j++;
		}
		i++;
	} 
}

void	print_ing_state_mess(t_command *test, int client_fd, t_world *g_world,
		t_client_manager *g_manager)
{
	if (!strcmp(test->type, "LOOK"))
		look_state_proc(test, client_fd, g_world, g_manager);
	else if (!strcmp(test->type, "WHO"))
		who_state_proc(test, g_manager);
	else if (!strcmp(test->type, "INVENTORY"))
		inventory_state_proc(test, g_manager, client_fd);
	else if (!strcmp(test->type, "STATUS"))
		status_state_proc(test, g_manager, client_fd);
	else if (!strcmp(test->type, "QUESTS"))
	{
		quests_state_proc(test, g_manager, g_world, client_fd);
		strcat(test->message, "]\n");
	}
	else if (!strcmp(test->type, "CONNECT"))
		connect_state_proc(test, g_manager, client_fd);
}

int	is_state(t_command test)
{
	if (!strcmp(test.type, "CONNECT"))
		return (1);
	else if (!strcmp(test.type, "LOOK"))
		return (1);
	else if (!strcmp(test.type, "WHO"))
		return (1);
	else if (!strcmp(test.type, "INVENTORY"))
		return (1);
	else if (!strcmp(test.type, "STATUS"))
		return (1);
	else if (!strcmp(test.type, "QUESTS"))
		return (1);
	else
		return (0);
}

t_signal	third_process(t_command test, int client_fd, t_world *g_world,
		t_client_manager *g_manager)
{
	t_signal	result;

	result.additional_group.number_of_them = 0;
	if (is_state(test))
	{
		print_ing_state_mess(&test, client_fd, g_world, g_manager);
		strcpy(result.specific_to_id_er, test.message);
		result.number_of_them = 1;
		result.all_fd[0] = client_fd;
	}
	else
	{
		if (room_concern(test))
			room_concern_act(&result, &test, client_fd, g_world);
	}
	return (result);
}
