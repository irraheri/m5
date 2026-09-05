/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_loop_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 06:13:25 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/05 12:09:20 by irraheri         ###   ########.fr       */
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
}

int	second_chance(char *result, t_line_type line_type)
{
	// bifurcation verification
}

t_line_type	second_next_line_type(t_line_type line_type)
{
	// bifurcation generation
}

t_line_type	next_line_type(t_line_type line_type)
{
	// generally non bifurcation
}
