/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 12:41:16 by irraheri          #+#    #+#             */
/*   Updated: 2026/08/27 18:11:53 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;
t_property			g_server;
t_client_manager	g_manager;

void	handle_shutdown(int sig)
{
	log_date();
	printf("Server shutdown...\n");
	close(g_server.server_fd);
	exit(0);
}

void	*client_host(void *arg)
{
	int		client_id;
	char	buf[1024];

	client_id = (int)(long)arg;
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		if (recv(client_id, buf, 1024, 0) <= 0)
			break ;
		printf("RECEIVED %s from socket %d\n", buf, client_id);
	}
	close(client_id);
	return (NULL);
}

void	server_routine(void)
{
	pthread_t	client_mess_rec;
	int			client_fd;

	client_fd = accept(g_server.server_fd, NULL, NULL);
	if (client_fd < 0)
		return ;
	add_player(client_fd, &g_manager);
	g_manager.number_of_player += 1;
	log_date();
	printf("Player %d is CONNECTED\n", g_manager.number_of_player);
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
	listen(g_server.server_fd, 5);
	initialize_client_manager(&g_manager);
	log_date();
	printf("Server is initialized\n");
	while (1)
		server_routine();
}
