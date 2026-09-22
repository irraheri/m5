#include <string.h>

typedef struct s_north_south_east_west
{
	char	dirs[4][8];
}			t_dir;

t_dir		define_dir(void);
void		look_c_add_exits(t_command *test, t_room room);
void		look_c_add_players(t_command *test, t_room room,
				t_client_manager *g_client_manager);
void		look_c_add_items(t_command *test, t_room room);
void		look_c_add_npcs(t_command *test, t_room room);
