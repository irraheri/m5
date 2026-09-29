#include "server.h"

static void	add_property(char *addr, t_player *attacker, t_player *target,
		int damage)
{
	char	buf[8];

	strcat(addr, " {\"attacker_hp\": ");
	sprintf(buf, "%d", attacker->hp);
	strcat(addr, buf);
	strcat(addr, ", \"target_hp\": ");
	sprintf(buf, "%d", target->hp);
	strcat(addr, buf);
	strcat(addr, ", \"damage\": ");
	sprintf(buf, "%d", damage);
	strcat(addr, buf);
	strcat(addr, ", \"status\": ");
	if (attacker->hp <= 0 || target->hp <= 0)
		strcat(addr, "\"end\"}\n");
	else
		strcat(addr, "\"combat\"}\n");
}

static void	generate_state(t_player *player)
{
	if (player->hp <= player->max_hp / 2 && player->hp > 0)
		strcpy(player->status_hp, "middle_healthy");
	else if (player->hp <= 0)
	{
		strcpy(player->name, "UNAUTHENTICATED");
		player->items.len = 0;
		player->quests.len = 0;
		player->hp = 100;
		player->max_hp = 100;
		player->attack = 10;
		strcpy(player->status_hp, "healthy");
	}
	else
		strcpy(player->status_hp, "healthy");
}

static void	attack_player(t_signal *result, t_command test, int client_fd,
		t_world *g_world)
{
	int			i;
	t_player	*you;
	t_player	*me;

	i = -1;
	while (++i < MAX_PLAYER)
	{
		if (!strcmp(g_world->client_manager->players[i].name, test.message))
			you = &(g_world->client_manager->players[i]);
		if (g_world->client_manager->players[i].fd == client_fd)
			me = &(g_world->client_manager->players[i]);
	}
	if (you->fd == me->fd || !strcmp(me->name, "UNAUTHENTICATED")
		|| !strcmp(you->name, "UNAUTHENTICATED"))
		return ;
	i = me->attack + 3 * generate_weighted_attack();
	you->hp -= i;
	me->hp -= you->attack;
	result->all_fd[0] = client_fd;
	result->all_fd[1] = you->fd;
	result->number_of_them = 2;
	strcpy(result->specific_to_id_er, "OK");
	add_property(result->specific_to_id_er, me, you, i);
	strcpy(result->message, "EVT YOU ARE ATTACKED BY ");
	strcat(result->message, me->name);
	add_property(result->message, me, you, i);
	generate_state(me);
	generate_state(you);
}

static int	name_in(char *element, t_list_of id_list, t_world *g_world)
{
	int	i;
	int	j;

	i = -1;
	while (++i < id_list.len)
	{
		j = -1;
		while (++j < MAX_PLAYER)
		{
			if (g_world->client_manager->players[j].fd == atoi(id_list.ids[i]))
			{
				if (!strcmp(g_world->client_manager->players[j].name, element))
					return (1);
			}
		}
	}
	return (0);
}

void	attack(t_signal *result, t_command test, int client_fd,
		t_world *g_world)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g_world->rooms.len)
	{
		j = -1;
		while (++j < g_world->rooms.rooms[i].players.len)
		{
			if (client_fd == atoi(g_world->rooms.rooms[i].players.ids[j]))
			{
				if (name_in(test.message, g_world->rooms.rooms[i].players,
						g_world))
					attack_player(result, test, client_fd, g_world);
				// else
				// 	attack_npc(result, test, client_fd, g_world);
			}
		}
	}
}
