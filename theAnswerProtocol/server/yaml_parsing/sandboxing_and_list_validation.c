/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandboxing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 00:25:29 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/05 02:06:57 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yaml.h"
#include <stdio.h>

void	key(char *line, char *sandbox)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = key_start(line);
	end = key_end(line);
	strcpy(sandbox, line);
	while (i + start < end)
	{
		sandbox[i] = sandbox[i + start];
		i++;
	}
	sandbox[i] = '\0';
}

void	value(char *line, char *sandbox)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = value_start(line) + 1;
	end = value_end(line);
	strcpy(sandbox, line);
	while (i + start < end)
	{
		sandbox[i] = sandbox[i + start];
		i++;
	}
	sandbox[i] = '\0';
}

int	validate_list(char *args)
{
	int	i;
	int	number_of_double_quotes;
	int	number_of_comma;

	i = 0;
	number_of_double_quotes = 0;
	number_of_comma = 0;
	while (args[i])
	{
		if (args[i] == '"')
			number_of_double_quotes++;
		if (args[i] == ',')
		{
			number_of_comma++;
			if (number_of_comma * 2 != number_of_double_quotes)
				return (-1);
		}
		i++;
	}
	return (0);
}
