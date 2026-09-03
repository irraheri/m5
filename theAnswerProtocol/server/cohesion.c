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
	if (!strcmp(buf, "CONNECT"))
		strcpy(result->type, "CONNECT");
	else if (!strcmp(buf, "MOVE"))
		strcpy(result->type, "MOVE");
	else if (!strcmp(buf, "TAKE"))
		strcpy(result->type, "TAKE");
	else if (!strcmp(buf, "DROP"))
		strcpy(result->type, "DROP");
	else if (!strcmp(buf, "TALK"))
		strcpy(result->type, "TALK");
	else if (!strcmp(buf, "ATTACK"))
		strcpy(result->type, "ATTACK");
	else if (!strcmp(buf, "QUEST"))
		strcpy(result->type, "QUEST");
	else if (!strcmp(buf, "CHAT"))
		strcpy(result->type, "CHAT");
	else if (!strcmp(buf, "GROUP"))
		strcpy(result->type, "GROUP");
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
	if (!strcmp(buf, "LOOK"))
		strcpy(result->type, "LOOK");
	else if (!strcmp(buf, "QUIT"))
		strcpy(result->type, "QUIT");
	else if (!strcmp(buf, "WHO"))
		strcpy(result->type, "WHO");
	else if (!strcmp(buf, "INVENTORY"))
		strcpy(result->type, "INVENTORY");
	else if (!strcmp(buf, "STATUS"))
		strcpy(result->type, "STATUS");
	else if (!strcmp(buf, "QUESTS"))
		strcpy(result->type, "QUESTS");
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
