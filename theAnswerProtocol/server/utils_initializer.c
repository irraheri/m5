/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_initializer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 12:41:18 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/04 16:15:52 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	print_ip_addr(void)
{
	char			hostname[256];
	struct hostent	*host_entry;
	char			ip[INET_ADDRSTRLEN];

	gethostname(hostname, sizeof(hostname));
	host_entry = gethostbyname(hostname);
	inet_ntop(AF_INET, host_entry->h_addr_list[0], ip, sizeof(ip));
	printf("%s\n", ip);
}

void	define_server_property(t_property *server_property)
{
	server_property->server_fd = socket(AF_INET, SOCK_STREAM, 0);
	server_property->address.sin_family = AF_INET;
	server_property->address.sin_addr.s_addr = INADDR_ANY;
	server_property->address.sin_port = htons(PORT);
}

void	log_date(void)
{
	time_t	timestamp;
	char	*date;

	timestamp = time(NULL);
	date = ctime(&timestamp);
	date[strlen(date) - 1] = '\0';
	printf("\r[%s] - ", date);
}

void	initialize_client_manager(t_client_manager *manager)
{
	int				i;

	i = 0;
	while (i < MAX_PLAYER)
	{
		manager->players[i].fd = -1;
		manager->players[i].status = 0;
		strcpy(manager->players[i].name, "none");
		manager->players[i].items.len = 0;
		manager->players[i].quests.len = 0;
		manager->players[i].hp = 100;
		manager->players[i].max_hp = 100;
		manager->players[i].attack = 10;
		strcpy(manager->players[i].status_hp, "healthy");
		i++;
	}
	manager->number_of_player = 0;
	manager->mutex = g_mutex;
}
