/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cohesion_third_process2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 06:34:27 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/28 09:46:35 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	fill_result(t_signal *result, char *player_name)
{
	strcpy(result->specific_to_id_er, "EVT ROOM PRESENCE LEAVE ");
	strcat(result->specific_to_id_er, player_name);
	strcat(result->specific_to_id_er, "\n");
	strcpy(result->message, "EVT ROOM PRESENCE LEAVE ");
	strcat(result->message, player_name);
	strcpy(result->additional_group.message, "EVT ROOM PRESENCE ENTER ");
	strcat(result->additional_group.message, player_name);
}

void	append(char *element, t_list_of *list)
{
	strcpy(list->ids[list->len], element);
	list->len++;
}

void	copy_all_player_in_room(t_signal *result, t_room *room)
{
	int	i;

	i = -1;
	while (++i < room->players.len)
		result->all_fd[i] = atoi(room->players.ids[i]);
	result->number_of_them = room->players.len;
}

static void	talk_utils(t_command *test, t_npc *npc, t_world *world)
{
	int	d_index;
	int	i;

	d_index = npc->dialogue_index;
	i = -1;
	while (++i < world->dialogues.len)
	{
		if (!strcmp(world->dialogues.dialogues[i].id,
				npc->dialogues.ids[d_index]))
		{
			strcat(test->message, world->dialogues.dialogues[i].content);
			npc->dialogue_index = (npc->dialogue_index + 1)
				% npc->dialogues.len;
			return ;
		}
	}
	strcat(test->message, "...");
}

static void	talk(t_room *room, t_command *test, t_world *world)
{
	int	k;
	int	i;

	k = -1;
	while (++k < room->npcs.len)
	{
		if (!strcmp(room->npcs.ids[k], test->message))
		{
			i = -1;
			while (++i < world->npcs.len)
			{
				if (!strcmp(world->npcs.npcs[i].id, test->message))
				{
					strcpy(test->message, "OK ");
					talk_utils(test, &(world->npcs.npcs[i]), world);
					strcat(test->message, "\n");
					break ;
				}
			}
			return ;
		}
	}
	strcpy(test->message, "ERR 404 NPC_NOT_FOUND\n");
	return ;
}

void	talk_state_proc(t_command *test, int client_fd, t_world *g_world)
{
	int	room;
	int	j;

	room = -1;
	while (++room < g_world->rooms.len)
	{
		j = -1;
		while (++j < g_world->rooms.rooms[room].players.len)
		{
			if (client_fd == atoi(g_world->rooms.rooms[room].players.ids[j]))
				talk(&(g_world->rooms.rooms[room]), test, g_world);
		}
	}
}
