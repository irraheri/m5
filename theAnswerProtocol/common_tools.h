#define MAX_PLAYER 512


typedef struct
{
    room *loc[128];
    int number_of_room;
} world;


typedef struct
{
    char room_id[256];
    int room_len;

    char name[128];
    int name_len;

    char description[512];
    int description_len;

    char *directions[4];
    char *exits[4];
    int exit_count;

    char *players[128];
    int players_len;

    char *items[16];
    int items_len;

    char *npcs[8];
    int npcs_len;

} room;


typedef struct
{
    char player_name[64];
    int player_name_len;

    int hp;
    int max_hp;

    char status[7];
    int turn;

    int attack_damage;

    int max_item_capacity;
} player;


typedef struct
{
    char item_id[256];
    int item_id_len;

    char name[128];
    int name_len;

    char description[512];
    int description_len;

    int obtainable;
    int hp_adding;
    int hp_adding_still_consumable_by_its_owner;
    int attack_damage_adding;
    int attack_damage_adding_still_consumable_by_its_owner;

    char *players_having_dropped_it[MAX_PLAYER];
    int players_having_dropped_it_len;
} item;


typedef struct
{
    int mission;

    char quest_id[256];
    int quest_id_len;

    char name[128];
    int name_len;

    char description[512];
    int description_len;

    char reward[256];
    int reward_len;

    char reward_name[128];
    int reward_name_len;

    char *players_having_finished_it[MAX_PLAYER];
    int players_having_finished_it_len;
} quest;


typedef struct
{
    char npc_id[256];
    int npc_id_len;

    char name[128];
    int name_len;

    char description[512];
    int description_len;

    int hp;

    char *dialogues[16];
    int dialogue_len;
    int dialogues_current_id;

    int hostile;

    char quest_id[256];
    int quest_id_len;
} npc;


typedef struct
{
    world world0;

    item items[512];
    int items_len;

    npc npcs[512];
    int npcs_len;

    quest quests[512];
    int quests_len;

    int max_hp;
    int attack_damage;
    int max_item_capacity;
} t_data;
