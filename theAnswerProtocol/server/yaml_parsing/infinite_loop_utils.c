/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_loop_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 06:13:25 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/07 11:12:32 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yaml.h"

t_world_creator	g_world_creator;

void	initialize_world_creator(void)
{
	strcpy(g_world_creator.current_creation, "world");
}

void	add_something(char *result, t_line_type line_type)
{
	return ;		
}

int	second_chance(char *result, t_line_type line_type)
{
	return (1);
}

t_line_type	second_next_line_type(t_line_type line_type)
{
	if (!strcmp(line_type.key, "room_id"))
	{
		strcmp(g_world_creator.current_creation, "items");
		return (generate_line_type(0, "items", 0, "none"));
	}
}

t_line_type	next_line_type(t_line_type line_type)
{
	if (!strcmp(line_type.key, "world"))
	{
		strcpy(g_world_creator.current_creation, "room_id");
		return (generate_line_type(1, "none", 0, "none"));
	}
	else if (!strcmp(line_type.key, "room_id"))
	{
		strcmp(g_world_creator.current_creation, "room_name");
		return (generate_line_type(2, "name", 1, "str"));
	}
	else if (!strcmp(line_type.key, "name") && !strcmp(g_world_creator.current_creation, "room_name"))
	{
		strcmp(g_world_creator.current_creation, "room_description");
		return (generate_line_type(2, "description", 1, "str"));
	}
	else if (!strcmp(line_type.key, "description") && !strcmp(g_world_creator.current_creation, "room_description"))
	{
		strcmp(g_world_creator.current_creation, "room_exits");
		return (generate_line_type(2, "exits", 1, "list"));
	}
	else if (!strcmp(line_type.key, "exits") && !strcmp(g_world_creator.current_creation, "room_exits"))
	{
		strcmp(g_world_creator.current_creation, "room_npcs");
		return (generate_line_type(2, "npcs", 1, "list"));
	}
	else if (!strcmp(line_type.key, "npcs") && !strcmp(g_world_creator.current_creation, "room_npcs"))
	{
		strcmp(g_world_creator.current_creation, "room_items");
		return (generate_line_type(2, "items", 1, "list"));
	}
	else if (!strcmp(line_type.key, "items" && !strcmp(g_world_creator.current_creation, "room_npcs")))
	{
		strcpy(g_world_creator.current_creation, "room_id");
		return (generate_line_type(1, "none", 0, "none"));
	}
}
