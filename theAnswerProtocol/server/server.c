/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 12:41:16 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/02 11:47:06 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_property			g_server;
t_client_manager	g_manager;

void	handle_shutdown(int sig)
{
	log_date();
	printf("Server shutdown...\n");
	close(g_server.server_fd);
	exit(0);
}

void	server_act(t_signal rec)
{
	int	i;

	i = 0;
	while (i < rec.number_of_them)
	{
		send(rec.all_fd[i], rec.message, strlen(rec.message), 0);
		i++;
	}
}

void	*client_host(void *arg)
{
	int			client_id;
	char		buf[BUFFER_SIZE];
	t_signal	rec;

	client_id = (int)(long)arg;
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		if (recv(client_id, buf, 1024, 0) <= 0)
		{
			log_date();
			printf("Player %d DISCONNECTED\n", player_id(client_id, g_manager));
			remove_player(client_id, &g_manager);
			break ;
		}
		log_date();
		buf[strlen(buf) - 1] = '\0';
		printf("RECEIVED '%s' FROM PLAYER %d\n", buf, player_id(client_id,
				g_manager));
		rec = cohesion(client_id, buf);
		server_act(rec);
	}
	close(client_id);
	return (NULL);
}

void	server_routine(void)
{
	pthread_t			client_mess_rec;
	int					client_fd;
	char				client_ip[INET_ADDRSTRLEN];
	struct sockaddr_in	client_addr;
	socklen_t			addr_len;

	addr_len = sizeof(client_addr);
	client_fd = accept(g_server.server_fd, (struct sockaddr *)&client_addr,
			&addr_len);
	if (client_fd < 0)
		return ;
	pthread_mutex_lock(&(g_manager.mutex));
	add_player(client_fd, &g_manager);
	g_manager.number_of_player += 1;
	pthread_mutex_unlock(&(g_manager.mutex));
	inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
	log_date();
	printf("Player %d is CONNECTED (%s)\n", player_id(client_fd, g_manager),
		client_ip);
	pthread_create(&client_mess_rec, NULL, client_host,
		(void *)(long)client_fd);
	pthread_detach(client_mess_rec);
}

int	main(void)
{
	log_date();
	printf("Server IP address: ");
	print_ip_addr();
	define_server_property(&g_server);
	signal(SIGINT, handle_shutdown);
	signal(SIGTERM, handle_shutdown);
	bind(g_server.server_fd, (struct sockaddr *)&(g_server.address),
		sizeof(g_server.address));
	listen(g_server.server_fd, 128);
	initialize_client_manager(&g_manager);
	log_date();
	printf("Server is initialized\n");
	while (1)
		server_routine();
}
