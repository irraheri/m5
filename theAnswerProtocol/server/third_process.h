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
