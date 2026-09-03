#include "cohesion.h"
#include "server.h"

int	intermediate_step(t_command test, t_command *result, int chat)
{
	strcat(result->type, test.message);
	restore_from_first_term(test.message);
	not_first_term(test.message);
	if (chat == 1)
	{
		strcpy(result->message, test.message);
		return (1);
	}
	else
	{
		if (first_term(test.message) == 0)
		{
			strcpy(result->message, test.message);
			return (1);
		}
	}
	return (0);
}

int	chat_and_group_management(t_command test, t_command *result)
{
	if (!strcmp(test.type, "CHAT"))
	{
		if (!strcmp(test.message, "GLOBAL") || !strcmp(test.message, "ROOM")
			|| !strcmp(test.message, "GROUP"))
			return (intermediate_step(test, result, 1));
	}
	else if (!(strcmp(test.type, "GROUP")))
	{
		if (!strcmp(test.message, "CREATE") || !strcmp(test.message, "INVITE")
			|| !strcmp(test.message, "JOIN") || !strcmp(test.message, "LEAVE"))
			return (intermediate_step(test, result, 0));
	}
	else
		;
	return (0);
}

void	first_word_parsing_mess(t_command test, t_command *result)
{
	result->is_valid = 1;
	strcpy(result->type, test.type);
	if (!strcmp(test.type, "TAKE") || !strcmp(test.type, "DROP"))
	{
		restore_from_first_term(test.message);
		strcpy(result->message, test.message);
		return ;
	}
	else if (!(strcmp(test.type, "CHAT")) || !(strcmp(test.type, "GROUP")))
	{
		if (chat_and_group_management(test, result) == 1)
			return ;
	}
	else
		;
	result->is_valid = 0;
	strcpy(result->type, "ERROR");
	strcpy(result->message, "ERR 901 SEND_FAILED\n");
}

void	one_word_parsing_mess(t_command test, t_command *result)
{
	result->is_valid = 1;
	strcpy(result->message, test.message);
	if (!strcmp(test.type, "CONNECT") || !strcmp(test.type, "MOVE")
		|| !strcmp(test.type, "TAKE") || !strcmp(test.type, "DROP")
		|| !strcmp(test.type, "TALK") || !strcmp(test.type, "ATTACK")
		|| !strcmp(test.type, "QUEST"))
		strcpy(result->type, test.type);
	else
	{
		result->is_valid = 0;
		strcpy(result->type, "ERROR");
		strcpy(result->message, "ERR 901 SEND_FAILED\n");
	}
}

t_command	second_process(t_command test)
{
	t_command	result;

	if (!strcmp(test.message, "one column message\n"))
		return (test);
	else if (first_term(test.message) == 0)
		one_word_parsing_mess(test, &result);
	else
		first_word_parsing_mess(test, &result);
	return (result);
}
