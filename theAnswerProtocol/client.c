/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 06:53:12 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/02 09:31:26 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

void	*wait_for_server(void *arg)
{
	char	buffer[BUFFER_SIZE];
	int		sock;

	sock = *(int *)(arg);
	while (1)
	{
		memset(buffer, 0, BUFFER_SIZE);
		recv(sock, buffer, BUFFER_SIZE, 0);
		pthread_mutex_lock(&mutex);
		printf("Serveur: %s", buffer);
		pthread_mutex_unlock(&mutex);
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
		send(sock, buffer, strlen(buffer), 0);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t			client_mods[2];
	int					sock;
	struct sockaddr_in	addr;

	if (argc != 2)
	{
		printf("NOT OK!\n");
		return (1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	connect(sock, (struct sockaddr *)&addr, sizeof(addr));
	printf("Connecté au serveur\n");
	pthread_create(&(client_mods[0]), NULL, wait_for_server, &sock);
	pthread_create(&(client_mods[1]), NULL, wait_for_client, &sock);
	pthread_join(client_mods[0], NULL);
	pthread_join(client_mods[1], NULL);
	close(sock);
	return (0);
}
