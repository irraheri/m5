#include "server.h"

void	connect_state_proc(t_command *test, t_client_manager *g_manager,
			int client_id)
{
    int i;

    i = 0;
    while (i < g_manager->number_of_player)
    {
        if (!strcmp(test->message, g_manager->players[i].name))
        {
            strcpy(test->message, "ERR 201 NAME_IN_USE\n");
            break;
        }
        i ++;
    }
    if (strcmp(test->message, "ERR 201 NAME_IN_USE\n"))
    {
        i = 0;
        while (i < g_manager->number_of_player)
        {
            if (g_manager->players[i].fd == client_id)
            {
                strcpy(g_manager->players[i].name, test->message);
                strcpy(test->message, "OK connected\n");
                break;
            }
            i ++;
        }
    }
}
