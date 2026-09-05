/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 15:09:51 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/05 05:51:43 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 128

typedef struct s_list_of
{
	char			ids[MAX_LEN][BUFFER_SIZE];
	int				len;
}					t_list_of;

typedef struct s_item
{
	char			id[BUFFER_SIZE];
	char			name[BUFFER_SIZE];
	char			description[BUFFER_SIZE];
	int				obtainable;
	int				heal;
}					t_item;

typedef struct npc
{
	char			id[BUFFER_SIZE];
	char			name[BUFFER_SIZE];
	char			description[BUFFER_SIZE];
	t_list_of		dialogues;
	int				dialogue_index;
	int				hp;
	int				attack;
	char			quest_id[BUFFER_SIZE];
}					t_npc;

typedef struct quest
{
	char			id[BUFFER_SIZE];
	char			name[BUFFER_SIZE];
	char			description[BUFFER_SIZE];
	t_list_of		missions;
	int				available;
	int				done;
	char			reward_id[BUFFER_SIZE];
	char			npc_owner_id[BUFFER_SIZE];
}					t_quest;

typedef struct mission
{
	char			id[BUFFER_SIZE];
	char			name[BUFFER_SIZE];
	char			description[BUFFER_SIZE];
	char			type[8];
	char			goal_id[BUFFER_SIZE];
}					t_mission;

typedef struct dialogue
{
	char			id[BUFFER_SIZE];
	char			content[BUFFER_SIZE];
}					t_dialogue;

typedef struct group
{
	char			name[BUFFER_SIZE];
	t_list_of		players;
}					t_group;

typedef struct room
{
	char			id[BUFFER_SIZE];
	char			name[BUFFER_SIZE];
	char			description[BUFFER_SIZE];
	t_list_of		exits;
	t_list_of		npcs;
	t_list_of		items;
	t_list_of		players;
}					t_room;

typedef struct all_items
{
	t_item			items[MAX_LEN];
	int				len;
}					t_all_items;

typedef struct all_npcs
{
	t_npc			npcs[MAX_LEN];
	int				len;
}					t_all_npcs;

typedef struct all_quests
{
	t_quest			quests[MAX_LEN];
	int				len;
}					t_all_quests;

typedef struct all_missions
{
	t_mission		missions[MAX_LEN];
	int				len;
}					t_all_missions;

typedef struct all_dialogues
{
	t_dialogue		dialogues[MAX_LEN];
	int				len;
}					t_all_dialogues;

typedef struct all_groups
{
	t_group			groups[MAX_LEN];
	int				len;
}					t_all_groups;

typedef struct all_rooms
{
	t_room			rooms[MAX_LEN];
	int				len;
}					t_all_rooms;

typedef struct world
{
	t_all_rooms		rooms;
	t_all_items		items;
	t_all_npcs		npcs;
	t_all_quests	quests;
	t_all_missions	missions;
	t_all_dialogues	dialogues;
	t_all_groups	groups;
}					t_world;
