/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_process_part_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 06:36:17 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/28 09:02:24 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	connection(t_command *test, t_client_manager *g_manager,
		int client_id)
{
	int	i;

	i = 0;
	while (i < g_manager->number_of_player)
	{
		if (g_manager->players[i].fd == client_id)
		{
			strcpy(g_manager->players[i].name, test->message);
			strcpy(test->message, "OK connected\n");
			break ;
		}
		i++;
	}
}

void	connect_state_proc(t_command *test, t_client_manager *g_manager,
		int client_id)
{
	int	i;

	i = 0;
	while (i < g_manager->number_of_player)
	{
		if (!strcmp(test->message, g_manager->players[i].name))
		{
			strcpy(test->message, "ERR 201 NAME_IN_USE\n");
			break ;
		}
		i++;
	}
	if (strcmp(test->message, "ERR 201 NAME_IN_USE\n"))
		connection(test, g_manager, client_id);
}

void	take(t_player *player, t_room *room, t_signal *result, t_command test)
{
	if (in(test.message, room->items))
	{
		strcpy(result->specific_to_id_er, "OK taken=");
		strcat(result->specific_to_id_er, test.message);
		strcat(result->specific_to_id_er, "\n");
		remove_from_list(test.message, &(room->items));
		append(test.message, &(player->items));
		copy_all_player_in_room(result, room);
		strcpy(result->message, "EVT ROOM TAKEN ");
		strcat(result->message, test.message);
		strcat(result->message, "\n");
	}
	else
	{
		strcpy(result->specific_to_id_er, "ERR 404 ITEM_NOT_FOUND\n");
		result->number_of_them = 1;
	}
}

void	drop(t_player *player, t_room *room, t_signal *result, t_command test)
{
	if (in(test.message, player->items))
	{
		strcpy(result->specific_to_id_er, "OK dropped=");
		strcat(result->specific_to_id_er, test.message);
		strcat(result->specific_to_id_er, "\n");
		remove_from_list(test.message, &(player->items));
		append(test.message, &(room->items));
		copy_all_player_in_room(result, room);
		strcpy(result->message, "EVT ROOM DROPPED ");
		strcat(result->message, test.message);
		strcat(result->message, "\n");
	}
	else
	{
		strcpy(result->specific_to_id_er, "ERR 404 ITEM_NOT_IN_INVENTORY\n");
		result->number_of_them = 1;
	}
}

static void	take_drop(t_player *player, t_room *room, t_signal *result,
		t_command test)
{
	if (!strcmp(test.type, "TAKE"))
		take(player, room, result, test);
	else
		drop(player, room, result, test);
}

static int	find_player_index(int client_fd, t_world *g_world)
{
	int	i;

	i = -1;
	while (++i < MAX_PLAYER)
		if (g_world->client_manager->players[i].fd == client_fd)
			return (i);
	return (-1);
}

void	take_drop_managing(t_signal *result, t_command test, int client_fd,
		t_world *g_world)
{
	int	i;
	int	j;
	int	player_;

	i = -1;
	player_ = find_player_index(client_fd, g_world);
	while (++i < g_world->rooms.len)
	{
		j = -1;
		while (++j < g_world->rooms.rooms[i].players.len)
		{
			if (atoi(g_world->rooms.rooms[i].players.ids[j]) == client_fd)
			{
				take_drop(&(g_world->client_manager->players[player_]),
					&(g_world->rooms.rooms[i]), result, test);
				return ;
			}
		}
	}
}
