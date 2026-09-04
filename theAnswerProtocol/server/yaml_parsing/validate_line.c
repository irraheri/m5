/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 02:10:36 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/05 02:48:51 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yaml.h"

int	is_validate(char *line, t_line_type norm)
{
	char	args[BUFFER_SIZE];

	if (level(line) != norm.level || key_start(line) == -1 || key_end(line)
		== -1)
		return (-1);
	if (norm.needs_arg == 0 && value_start(line) != -2)
		return (-1);
	if (norm.needs_arg == 1 && (value_start(line) < 0 || value_end(line) < 0))
		return (-1);
	if (!strcmp(norm.type, "str") && line[value_start(line)] != '['
		|| !strcmp(norm.type, "list") && line[value_start(line)] != '"')
		return (-1);
	if (!strcmp(norm.type, "list"))
	{
		value(line, args);
		if (validate_list(args) == -1)
			return (-1);
	}
	if (strcmp(norm.key, "none"))
	{
		key(line, args);
		if (strcmp(norm.key, args))
			return (-1);
	}
	return (0);
}

void	split_step(int *inside_quotes, int *curr, int *i, char *args)
{
	if (args[*i] == '"')
	{
		*inside_quotes = !(*inside_quotes);
		if (!(*inside_quotes))
			(*curr)++;
	}
}

int	split(char *args, int index, char *sandbox)
{
	int	i;
	int	j;
	int	curr;
	int	inside_quotes;

	i = 0;
	j = 0;
	curr = 0;
	inside_quotes = 0;
	while (args[i])
	{
		split_step(&inside_quotes, &curr, &i, args);
		if (inside_quotes && curr == index && args[i] != '"')
		{
			sandbox[j] = args[i];
			j++;
		}
		i++;
	}
	sandbox[j] = '\0';
	return (curr);
}
