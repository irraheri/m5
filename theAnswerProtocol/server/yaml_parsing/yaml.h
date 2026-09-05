/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yaml.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 23:54:48 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/05 06:17:39 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../world.h"
#define BUFFER_SIZE 1024

typedef struct line_type
{
	int			level;
	char		key[BUFFER_SIZE];
	int			needs_arg;
	char		type[BUFFER_SIZE];
}				t_line_type;

typedef struct world_creator
{
	char		current_creation[32];
	t_room		room_sample;
	t_item		item_sample;
	t_npc		npc_sample;
	t_quest		quest_sample;
	t_mission	mission_sample;
	t_dialogue	dialogue_sample;
	t_group		group_sample;
	t_world		world;
}				t_world_creator;

int				level(char *line);
int				key_start(char *line);
int				key_end(char *line);
int				value_start(char *line);
int				value_end(char *line);

void			key(char *line, char *sandbox);
void			value(char *line, char *sandbox);
int				validate_list(char *args);

int				is_valid(char *line, t_line_type norm);
int				split(char *args, int index, char *sandbox);
void			initialize_world_creator(void);
