/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_process.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 06:36:33 by irraheri          #+#    #+#             */
/*   Updated: 2026/09/28 13:19:00 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

void	who_state_proc(t_command *test, t_client_manager *g_manager);
void	inventory_state_proc(t_command *test, t_client_manager *g_manager,
			int client_id);
void	status_state_proc(t_command *test, t_client_manager *g_manager,
			int client_id);
void	quests_state_proc(t_command *test, t_client_manager *g_manager,
			t_world *world, int client_id);
void	connect_state_proc(t_command *test, t_client_manager *g_manager,
			int client_id);
void	take_drop_managing(t_signal *result, t_command test, int client_fd,
			t_world *g_world);
void	talk_state_proc(t_command *test, int client_fd, t_world *g_world);
