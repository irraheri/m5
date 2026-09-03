/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 12:41:20 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/03 11:00:14 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "../common.h"

typedef struct server_fd_plus_address
{
	int					server_fd;
	struct sockaddr_in	address;
}						t_property;

typedef struct each_player_property
{
	int					fd;
	int					status;
}						t_player;

typedef struct making_player_list
{
	t_player			players[MAX_PLAYER];
	int					number_of_player;
	pthread_mutex_t		mutex;
}						t_client_manager;

typedef struct signal_from_backend
{
	int					all_fd[MAX_PLAYER];
	int					number_of_them;
	char				message[BUFFER_SIZE];
}						t_signal;

typedef struct command_struct
{
	int					is_valid;
	char				type[32];
	char				message[128];
}						t_command;

void					log_date(void);
void					print_ip_addr(void);
void					define_server_property(t_property *server_property);
void					initialize_client_manager(t_client_manager *manager);
void					add_player(int client_fd, t_client_manager *manager);
t_signal				cohesion(int client_fd, char *buf);
int						player_id(int client_fd, t_client_manager gmanager);
void					remove_player(int client_fd, t_client_manager *manager);

#endif
