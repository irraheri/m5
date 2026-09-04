#include "cohesion.h"

void	multi_word_parsing(char *buf, t_command *result)
{
	if (!strcmp(result->type, "ERROR"))
		return ;
	strcpy(result->message, buf);
}

void	first_word_parsing(char *buf, t_command *result)
{
	result->is_valid = 1;
	if (!strcmp(buf, "CONNECT") || !strcmp(buf, "MOVE") || !strcmp(buf, "TAKE")
		|| !strcmp(buf, "DROP") || !strcmp(buf, "TALK") || !strcmp(buf,
			"ATTACK") || !strcmp(buf, "QUEST") || !strcmp(buf, "CHAT")
		|| !strcmp(buf, "GROUP"))
		strcpy(result->type, buf);
	else
	{
		result->is_valid = 0;
		strcpy(result->type, "ERROR");
		strcpy(result->message, "ERR 901 SEND_FAILED\n");
	}
}

void	one_word_parsing(char *buf, t_command *result)
{
	result->is_valid = 1;
	strcpy(result->message, "one column message\n");
	if (!strcmp(buf, "LOOK") || !strcmp(buf, "QUIT") || !strcmp(buf, "WHO")
		|| !strcmp(buf, "INVENTORY") || !strcmp(buf, "STATUS") || !strcmp(buf,
			"QUESTS"))
		strcpy(result->type, buf);
	else
	{
		result->is_valid = 0;
		strcpy(result->type, "ERROR");
		strcpy(result->message, "ERR 901 SEND_FAILED\n");
	}
}

t_command	first_process(char *buf)
{
	t_command	result;

	if (first_term(buf) == 0)
		one_word_parsing(buf, &result);
	else
	{
		first_word_parsing(buf, &result);
		restore_from_first_term(buf);
		not_first_term(buf);
		multi_word_parsing(buf, &result);
	}
	return (result);
}

t_signal	cohesion(int client_fd, char *buf)
{
	t_signal	sign;
	t_command	test;

	test = first_process(buf);
	if (test.is_valid == 0)
	{
		sign.number_of_them = 1;
		sign.all_fd[0] = client_fd;
		strcpy(sign.message, test.message);
		return (sign);
	}
	else
	{
		test = second_process(test);
		if (test.is_valid == 0)
		{
			sign.number_of_them = 1;
			sign.all_fd[0] = client_fd;
			strcpy(sign.message, test.message);
			return (sign);
		}
		else
			return (third_process(test, client_fd));
	}
}
