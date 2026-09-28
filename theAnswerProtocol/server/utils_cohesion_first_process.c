#include "server.h"

int	first_term(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (i == strlen(str))
		return (0);
	else
	{
		str[i] = '\0';
		return (1);
	}
}

void	restore_from_first_term(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	str[i] = ' ';
}

void	not_first_term(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (i == strlen(str))
		return ;
	else
	{
		i++;
		while (str[i])
		{
			str[j] = str[i];
			j++;
			i++;
		}
		str[j] = '\0';
	}
}

int			in(char *element, t_list_of list)
{
	int i;

	i = -1;
	while (++i < list.len)
	{
		if (!strcmp(list.ids[i], element))
			return (1);
	}
	return (0);
}

void		remove_from_list(char *element, t_list_of *list)
{
	int i;
	int j;

	i = 0;
	while (i < list->len)
	{
		if (!strcmp(list->ids[i], element))
		{
			j = i;
			while (j < list->len - 1)
			{
				strcpy(list->ids[j], list->ids[j + 1]);
				j ++;
			}
			list->len --;
			break;
		}
		i ++;
	}
}
