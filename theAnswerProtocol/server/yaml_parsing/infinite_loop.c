/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 06:12:11 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/05 06:22:30 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../world.h"
#include "yaml.h"

t_line_type	generate_line_type(int level, char *key, int needs_arg, char *type)
{
	t_line_type	result;

	result.level = level;
	strcpy(result.key, key);
	result.needs_arg = needs_arg;
	strcpy(result.type, type);
	return (result);
}

void	infinite_loop(FILE *f, char *result)
{
	t_line_type	line_type;
	int			valid_line;

	line_type = generate_line_type(0, "world", 0, "none");
	while (fgets(result, BUFFER_SIZE, f))
	{
		result[strlen(result) - 1] = '\0';
		valid_line = is_valid(result, line_type);
		if (valid_line == 1)
			add_something(result, line_type);
		else
		{
			if (second_chance(result, line_type))
			{
				line_type = second_next_line_type(line_type);
				add_something(result, line_type);
			}
			else
			{
				printf("Invalid world.yaml in the line %s\n", result);
				exit(1);
			}
		}
		line_type = next_line_type(line_type);
	}
}

void	load_world(const char *path)
{
	FILE	*f;
	char	result[BUFFER_SIZE];

	f = fopen(path, "r");
	if (!f)
	{
		printf("error while loading the 'world.yaml' file");
		exit(0);
	}
	initialize_world_creator();
	infinite_loop(f, result);
}

int	main(void)
{
	load_world("../../world.yaml");
	return (1);
}
