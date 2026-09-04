/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_indexing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 23:53:10 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/05 00:51:45 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yaml.h"

int	level(char *line)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (line[i] == ' ' && line[i + 1] == ' ')
			i += 2;
		else
			break ;
	}
	return (i / 2);
}

int	key_start(char *line)
{
	return (level(line) * 2);
}

int	key_end(char *line)
{
	int	current_key;

	current_key = level(line) * 2;
	while (line[current_key] != ':' && line[current_key])
		current_key++;
	if (line[current_key] == '\0')
		return (-1);
	return (current_key);
}

int	value_start(char *line)
{
	int	key_end_;
	int	i;

	key_end_ = key_end(line);
	if (key_end_ == -1)
		return (-1);
	key_end_ += 2;
	if (key_end_ >= strlen(line))
		return (-2);
	else if (line[key_end_] == '[' || line[key_end_] == '"')
		return (key_end_);
	else
		return (-1);
}

int	value_end(char *line)
{
	int	start;

	start = value_start(line);
	if (start < 0)
		return (-1);
	if (line[start] == '[')
	{
		start++;
		while (line[start] != ']' && line[start])
			start++;
		if (line[start] == '\0' || line[start + 1] != '\0')
			return (-1);
		else
			return (start);
	}
	else
	{
		start++;
		while (line[start] != '"' && line[start])
			start++;
		if (line[start] == '\0' || line[start + 1] != '\0')
			return (-1);
		else
			return (start);
	}
}
