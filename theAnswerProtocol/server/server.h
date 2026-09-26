/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 12:41:20 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/26 08:45:42 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common.h"
#include "world.h"

typedef struct server_fd_plus_address
{
	int					server_fd;
	struct sockaddr_in	address;
}						t_property;

typedef struct each_player_property
{
	int					fd;
	int					status;
	char				name[32];
	t_list_of			items;
	t_list_of			quests;
	int					hp;
	int					max_hp;
	int					attack;
	char				status_hp[16];
}						t_player;

typedef struct making_player_list
{
	t_player			players[MAX_PLAYER];
	int					number_of_player;
	pthread_mutex_t		mutex;
}						t_client_manager;

typedef struct additional_group
{
	int					all_fd[MAX_PLAYER];
	int					number_of_them;
	char				message[BUFFER_SIZE];
}						t_additional;

typedef struct signal_from_backend
{
	int					all_fd[MAX_PLAYER];
	int					number_of_them;
	char				message[BUFFER_SIZE];
	char				specific_to_id_er[BUFFER_SIZE];
	t_additional		additional_group;
}						t_signal;

typedef struct command_struct
{
	int					is_valid;
	char				type[32];
	char				message[128];
}						t_command;

typedef struct world
{
	t_all_rooms			rooms;
	t_all_items			items;
	t_all_npcs			npcs;
	t_all_quests		quests;
	t_all_missions		missions;
	t_all_dialogues		dialogues;
	t_all_groups		groups;
	t_client_manager	*client_manager;
}						t_world;

void					log_date(void);
void					print_ip_addr(void);
void					define_server_property(t_property *server_property);
void					initialize_client_manager(t_client_manager *manager);
void					add_player(int client_fd, t_client_manager *manager,
							t_world *world);
int						player_id(int client_fd, t_client_manager gmanager);
void					remove_player(int client_fd, t_client_manager *manager);
void					remove_player_in_world(int client_fd, t_world *world);
t_signal				cohesion(int client_fd, char *buf, t_world *g_world,
							t_client_manager *g_manager);
int						room_concern(t_command test);
void					room_concern_act(t_signal *result, t_command *test,
							int client_fd, t_world *g_world);
void					initialize_world(t_world *world, t_client_manager *g_manager);
