/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yaml.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 23:54:48 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/05 02:49:34 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#define BUFFER_SIZE 1024

typedef struct line_type
{
	int		level;
	char	key[BUFFER_SIZE];
	int		needs_arg;
	char	type[BUFFER_SIZE];
}			t_line_type;

int			level(char *line);
int			key_start(char *line);
int			key_end(char *line);
int			value_start(char *line);
int			value_end(char *line);

void		key(char *line, char *sandbox);
void		value(char *line, char *sandbox);
int			validate_list(char *args);
