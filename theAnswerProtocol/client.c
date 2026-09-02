/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 06:53:12 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/02 10:56:39 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;
int				g_disconnect = 0;

void	*wait_for_server(void *arg)
{
	char	buffer[BUFFER_SIZE];
	int		sock;

	sock = *(int *)(arg);
	while (1)
	{
		memset(buffer, 0, BUFFER_SIZE);
		if (recv(sock, buffer, BUFFER_SIZE, 0) <= 0)
		{
			printf("DISCONNECTED SERVER!\n");
			g_disconnect = 1;
			return (NULL);
		}
		pthread_mutex_lock(&g_mutex);
		printf("Serveur: %s", buffer);
		pthread_mutex_unlock(&g_mutex);
	}
	return (NULL);
}

void	*wait_for_client(void *arg)
{
	char	buffer[BUFFER_SIZE];
	int		sock;

	sock = *(int *)(arg);
	while (1)
	{
		memset(buffer, 0, BUFFER_SIZE);
		fgets(buffer, BUFFER_SIZE, stdin);
		if (g_disconnect == 1)
			break ;
		send(sock, buffer, strlen(buffer), 0);
	}
	return (NULL);
}

int	end(int sock)
{
	printf("END OF THE PROGRAM\n");
	close(sock);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t			client_mods[2];
	int					sock;
	struct sockaddr_in	addr;

	if (argc != 2)
	{
		printf("Please use the format ./client <server-ip-addr>\n");
		return (1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		printf("NO SERVER TO CONNECT WITH!\n");
		return (end(sock));
	}
	printf("Connecté au serveur\n");
	pthread_create(&(client_mods[0]), NULL, wait_for_server, &sock);
	pthread_create(&(client_mods[1]), NULL, wait_for_client, &sock);
	pthread_join(client_mods[0], NULL);
	pthread_join(client_mods[1], NULL);
	return (end(sock));
}
