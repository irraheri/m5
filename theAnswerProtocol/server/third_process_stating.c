#include "server.h"

void	who_state_proc(t_command *test, t_client_manager *g_manager)
{
	char	rand_buf[6];

	sprintf(rand_buf, "%d", g_manager->number_of_player);
	strcpy(test->message, "OK players=");
	strcat(test->message, rand_buf);
	strcat(test->message, "\n");
}

void	inventory_state_proc(t_command *test, t_client_manager *g_manager,
		int client_id)
{
	int	client_;
	int	d;

	strcpy(test->message, "OK [");
	client_ = 0;
	while (client_ < g_manager->number_of_player)
	{
		if (client_id == g_manager->players[client_].fd)
		{
			d = 0;
			while (d < g_manager->players[client_].items.len)
			{
				if (d != 0)
					strcat(test->message, ", ");
				strcat(test->message, "\"");
				strcat(test->message, g_manager->players[client_].items.ids[d]);
				strcat(test->message, "\"");
				d++;
			}
			break ;
		}
		client_++;
	}
	strcat(test->message, "]\n");
}

void status_state_proc(t_command *test, t_client_manager *g_manager, int client_id)
{
	int	client_;
	char rand_buf[5];

	strcpy(test->message, "OK {");
	client_ = 0;
	while (client_ < g_manager->number_of_player)
	{
		if (client_id == g_manager->players[client_].fd)
		{
			strcat(test->message, "\"hp\": ");
			sprintf(rand_buf, "%d", g_manager->players[client_].hp);
			strcat(test->message, rand_buf);
			strcat(test->message, ", \"max_hp\": ");
			sprintf(rand_buf, "%d", g_manager->players[client_].max_hp);
			strcat(test->message, rand_buf);
			strcat(test->message, ", \"status\": \"");
			strcat(test->message, g_manager->players[client_].status_hp);
			strcat(test->message, "\"");
			break ;
		}
		client_++;
	}
	strcat(test->message, "}\n");
}

static void quests_property(t_command *test, t_quest quest, int *k)
{
	int i;
	char buf_rand[4];

	i = 0;
	if (k != 0)
		strcat(test->message, ", ");
	strcat(test->message, "{");
	strcat(test->message, "\"quest_id\": ");
	strcat(test->message, quest.id);
	strcat(test->message, ", \"status\": ");
	if (!quest.done)
		strcat(test->message, "active, \"progress\": \"");
	else
		strcat(test->message, "done, \"progress\": \"");
	sprintf(buf_rand, "%d", quest.done_missions);
	strcat(test->message, buf_rand);
	strcat(test->message, "/");
	sprintf(buf_rand, "%d", quest.missions.len);
	strcat(test->message, buf_rand);
	strcat(test->message, "\"}");
	*k = *k + 1;
}

void quests_state_proc(t_command *test, t_client_manager *g_manager, t_world *world, int client_id)
{
	int client_;
	int i;
	int quest_id;
	int k;

	client_ = 0;
	k = 0;
	strcpy(test->message, "OK [");
	while (client_ < g_manager->number_of_player && client_id != g_manager->players[client_].fd)
		client_++;
	if (client_ < g_manager->number_of_player)
	{
		i = 0;
		while (i < g_manager->players[client_].quests.len)
		{
			quest_id = 0;
			while (quest_id < world->quests.len)
			{
				if (!strcmp(world->quests.quests[quest_id].id, g_manager->players[client_].quests.ids[i]))
					quests_property(test, world->quests.quests[quest_id], &k);
				quest_id++;
			}
			i++;
		}
	}
}
