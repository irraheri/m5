/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_concern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 06:22:51 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/28 13:22:44 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "third_process.h"

int	room_concern(t_command test)
{
	if (!strcmp(test.type, "MOVE"))
		return (1);
	else if (!strcmp(test.type, "TAKE") || !strcmp(test.type, "DROP"))
		return (1);
	else if (!strcmp(test.type, "ATTACK"))
		return (1);
	else
		return (0);
}

t_room	*room_result_config(t_signal *result, int client_fd, t_world *g_world)
{
	int		i;
	int		j;
	int		k;
	t_room	*room;

	i = -1;
	while (++i < g_world->rooms.len)
	{
		j = -1;
		while (++j < g_world->rooms.rooms[i].players.len)
		{
			if (atoi(g_world->rooms.rooms[i].players.ids[j]) != client_fd)
				continue ;
			k = -1;
			result->number_of_them = g_world->rooms.rooms[i].players.len;
			room = &(g_world->rooms.rooms[i]);
			while (++k < g_world->rooms.rooms[i].players.len)
				result->all_fd[k] = atoi(
						g_world->rooms.rooms[i].players.ids[k]);
		}
	}
	return (room);
}

int	move_from_to(t_signal *result, int client_fd, t_room *to, t_world *g_world)
{
	char	sample_buf[4];
	int		i;
	char	player_name[32];

	sprintf(sample_buf, "%d", client_fd);
	strcpy(to->players.ids[to->players.len], sample_buf);
	to->players.len += 1;
	i = 0;
	result->additional_group.number_of_them = to->players.len;
	while (i < to->players.len)
	{
		result->additional_group.all_fd[i] = atoi(to->players.ids[i]);
		i++;
	}
	i = 0;
	while (i < MAX_PLAYER)
	{
		if (g_world->client_manager->players[i].fd == client_fd)
			strcpy(player_name, g_world->client_manager->players[i].name);
		i++;
	}
	fill_result(result, player_name);
	return (1);
}

int	move_part(t_signal *result, int client_fd, t_world *g_world, t_room **room)
{
	t_dir	directions;
	int		i;
	int		j;

	directions = define_dir();
	i = 0;
	while (i < 4)
	{
		if (!strcmp(directions.dirs[i], result->message))
		{
			j = 0;
			while (j < g_world->rooms.len)
			{
				if (!strcmp(g_world->rooms.rooms[j].id, (*room)->exits.ids[i]))
				{
					_player_in_world(client_fd, g_world);
					(*room) = &(g_world->rooms.rooms[j]);
					return (move_from_to(result, client_fd, *room, g_world));
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}

void	room_concern_act(t_signal *result, t_command test, int client_fd,
		t_world *g_world)
{
	t_room	*room;

	if (!strcmp(test.type, "MOVE"))
	{
		room = room_result_config(result, client_fd, g_world);
		strcpy(result->message, test.message);
		if (move_part(result, client_fd, g_world, &room))
		{
			strcat(result->message, "\n");
			strcat(result->additional_group.message, "\n");
			strcat(result->specific_to_id_er, "OK room=");
			strcat(result->specific_to_id_er, room->id);
			strcat(result->specific_to_id_er, "\n");
		}
		else
		{
			result->all_fd[0] = client_fd;
			result->number_of_them = 1;
			strcpy(result->specific_to_id_er, "ERR 301 NO_EXIT\n");
		}
	}
	else
		take_drop_managing(result, test, client_fd, g_world);
}
