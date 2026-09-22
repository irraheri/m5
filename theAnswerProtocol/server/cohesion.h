#include "server.h"

int			first_term(char *str);
void		restore_from_first_term(char *str);
void		not_first_term(char *str);
t_command	second_process(t_command test);
t_signal	third_process(t_command test, int client_fd, t_world *g_world,
				t_client_manager *g_manager);
