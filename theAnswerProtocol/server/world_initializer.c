#include "world.h"

void	initialize_groups(t_all_groups *groups)
{
	t_list_of	player;

	player.len = 0;
	strcpy(groups->groups[0].name, "global");
	groups->groups[0].players = player;
	groups->len = 1;
}

void	initialize_dialogue(t_all_dialogues *dialogues)
{
	strcpy(dialogues->dialogues[0].id, "play_queen");
	strcpy(dialogues->dialogues[0].content,
		"The queen is the most versatile piece on the board.");
	strcpy(dialogues->dialogues[1].id, "play_rook");
	strcpy(dialogues->dialogues[1].content,
        "In the endgame, control of the rook's file is everything.");
	strcpy(dialogues->dialogues[2].id, "ithinksoiam");
	strcpy(dialogues->dialogues[2].content, "I think, therefore I am.");
	strcpy(dialogues->dialogues[3].id, "survivor");
	strcpy(dialogues->dialogues[3].content,
		"It is not the strongest that survive, but the most adaptable.");
	strcpy(dialogues->dialogues[4].id, "samsa");
	strcpy(dialogues->dialogues[4].content,
		"I awoke one morning to find myself transformed into something unrecognizable.");
	strcpy(dialogues->dialogues[5].id, "citation1");
	strcpy(dialogues->dialogues[5].content,
		"The mystery of existence is not in survival, but in meaning.");
	strcpy(dialogues->dialogues[6].id, "citation2");
	strcpy(dialogues->dialogues[6].content,
		"Suffering is the price of a deep consciousness.");
	strcpy(dialogues->dialogues[7].id, "citation3");
	strcpy(dialogues->dialogues[7].content,
		"Better to err on your own path than to walk another's perfectly.");
	strcpy(dialogues->dialogues[8].id, "doggy");
	strcpy(dialogues->dialogues[8].content,
        "The road is long, but the stories make it shorter.");
	strcpy(dialogues->dialogues[9].id, "pulpy");
	strcpy(dialogues->dialogues[9].content,
		"I've always been drawn to the edge of the law.");
	strcpy(dialogues->dialogues[10].id, "president_dialogue0");
	strcpy(dialogues->dialogues[10].content,
        "I have a vision, and it's unparalleled.");
	strcpy(dialogues->dialogues[11].id, "dialogues_about_religion");
	strcpy(dialogues->dialogues[11].content,
        "I believe in greatness, and I believe in grace.");
	dialogues->len = 12;
}

void	initialize_missions(t_all_missions *missions)
{
	strcpy(missions->missions[0].id, "take_diamond_from_trump");
	strcpy(missions->missions[0].type, "take");
	strcpy(missions->missions[0].goal_id, "diamond");
	strcpy(missions->missions[1].id, "neutralize_snoop");
	strcpy(missions->missions[1].type, "kill");
	strcpy(missions->missions[1].goal_id, "snoop_dogg");
	strcpy(missions->missions[2].id, "neutralize_saitama");
	strcpy(missions->missions[2].type, "kill");
	strcpy(missions->missions[2].goal_id, "saitama");
	strcpy(missions->missions[3].id, "acquire_gold");
	strcpy(missions->missions[3].type, "take");
	strcpy(missions->missions[3].goal_id, "gold");
	strcpy(missions->missions[4].id, "acquire_rook");
	strcpy(missions->missions[4].type, "take");
	strcpy(missions->missions[4].goal_id, "rook");
	strcpy(missions->missions[5].id, "acquire_stone");
	strcpy(missions->missions[5].type, "take");
	strcpy(missions->missions[5].goal_id, "philosophical_stone");
	missions->len = 6;
}

void	initialize_quests(t_all_quests *quests)
{
	t_list_of	missions[MAX_LEN];

	strcpy(missions[0].ids[0], "take_diamond_from_trump");
	missions[0].len = 1;
	strcpy(quests->quests[0].id, "trump_diamond");
	strcpy(quests->quests[0].name, "The Exchange");
	strcpy(quests->quests[0].description,
		"Retrieve the diamond from the hilltop and bring it to the atelier.");
	quests->quests[0].missions = missions[0];
	strcpy(quests->quests[0].reward_id, "none");
	strcpy(quests->quests[0].npc_owner_id, "pablo_picasso");
	quests->quests[0].available = 1;
	quests->quests[0].done = 0;
	strcpy(missions[1].ids[0], "neutralize_snoop");
	strcpy(missions[1].ids[1], "neutralize_saitama");
	missions[1].len = 2;
	strcpy(quests->quests[1].id, "doogy_saitama");
	strcpy(quests->quests[1].name, "The Clearing");
	strcpy(quests->quests[1].description,
		"Remove the wanderer and the bored one to restore peace to the crossroads.");
	quests->quests[1].missions = missions[1];
	strcpy(quests->quests[1].reward_id, "philosophical_stone");
	strcpy(quests->quests[1].npc_owner_id, "franz_kafka");
	quests->quests[1].available = 1;
	quests->quests[1].done = 0;
	strcpy(missions[2].ids[0], "acquire_gold");
	strcpy(missions[2].ids[1], "acquire_rook");
	strcpy(missions[2].ids[2], "acquire_stone");
	missions[2].len = 3;
	strcpy(quests->quests[2].id, "gold_rook");
	strcpy(quests->quests[2].name, "The Trilogy");
	strcpy(quests->quests[2].description,
		"Gather the three relics to complete the director's vision.");
	quests->quests[2].missions = missions[2];
	strcpy(quests->quests[2].reward_id, "oscar");
	strcpy(quests->quests[2].npc_owner_id, "martin_scorsesse");
	quests->quests[2].available = 1;
	quests->quests[2].done = 0;
	quests->len = 3;
}

void	initialize_npcs(t_all_npcs *npcs)
{
	t_list_of	dialogues[MAX_LEN];

	strcpy(dialogues[0].ids[0], "play_queen");
	strcpy(dialogues[0].ids[1], "play_rook");
	dialogues[0].len = 2;
	strcpy(npcs->npcs[0].id, "magnus_carlsen");
	strcpy(npcs->npcs[0].name, "Grandmaster Magnus");
	strcpy(npcs->npcs[0].description,
        "The reigning champion of the board, calm and calculating.");
	npcs->npcs[0].dialogues = dialogues[0];
	npcs->npcs[0].dialogue_index = 0;
	npcs->npcs[0].hp = -1;
	npcs->npcs[0].attack = -1;
	strcpy(npcs->npcs[0].quest_id, "none");
	strcpy(dialogues[1].ids[0], "ithinksoiam");
	dialogues[1].len = 1;
	strcpy(npcs->npcs[1].id, "rene_descartes");
	strcpy(npcs->npcs[1].name, "René the Skeptic");
	strcpy(npcs->npcs[1].description,
        "A philosopher in a worn cloak, forever doubting, forever thinking.");
	npcs->npcs[1].dialogues = dialogues[1];
	npcs->npcs[1].dialogue_index = 0;
	npcs->npcs[1].hp = -1;
	npcs->npcs[1].attack = -1;
	strcpy(npcs->npcs[1].quest_id, "none");
	strcpy(dialogues[2].ids[0], "survivor");
	dialogues[2].len = 1;
	strcpy(npcs->npcs[2].id, "charles_darwin");
	strcpy(npcs->npcs[2].name, "Charles the Naturalist");
	strcpy(npcs->npcs[2].description,
        "A bearded man with a notebook, observing the world with quiet intensity.");
	npcs->npcs[2].dialogues = dialogues[2];
	npcs->npcs[2].dialogue_index = 0;
	npcs->npcs[2].hp = -1;
	npcs->npcs[2].attack = -1;
	strcpy(npcs->npcs[2].quest_id, "none");
	dialogues[3].len = 0;
	strcpy(npcs->npcs[3].id, "pablo_picasso");
	strcpy(npcs->npcs[3].name, "Pablo the Visionary");
	strcpy(npcs->npcs[3].description,
        "A painter with piercing eyes, always ready to reshape reality.");
	npcs->npcs[3].dialogues = dialogues[3];
	npcs->npcs[3].dialogue_index = 0;
	npcs->npcs[3].hp = -1;
	npcs->npcs[3].attack = -1;
	strcpy(npcs->npcs[3].quest_id, "trump_diamond");
	strcpy(dialogues[4].ids[0], "samsa");
	dialogues[4].len = 1;
	strcpy(npcs->npcs[4].id, "franz_kafka");
	strcpy(npcs->npcs[4].name, "Franz the Scribe");
	strcpy(npcs->npcs[4].description,
        "A pale, anxious figure, haunted by the absurdity of bureaucracy.");
	npcs->npcs[4].dialogues = dialogues[4];
	npcs->npcs[4].dialogue_index = 0;
	npcs->npcs[4].hp = -1;
	npcs->npcs[4].attack = -1;
	strcpy(npcs->npcs[4].quest_id, "doogy_saitama");
	strcpy(dialogues[5].ids[0], "citation1");
	strcpy(dialogues[5].ids[1], "citation2");
	strcpy(dialogues[5].ids[2], "citation3");
	dialogues[5].len = 3;
	strcpy(npcs->npcs[5].id, "fiodor_dostoievsky");
	strcpy(npcs->npcs[5].name, "Fyodor the Confessor");
	strcpy(npcs->npcs[5].description,
        "A gaunt man with feverish eyes, speaking of suffering and redemption.");
	npcs->npcs[5].dialogues = dialogues[5];
	npcs->npcs[5].dialogue_index = 0;
	npcs->npcs[5].hp = -1;
	npcs->npcs[5].attack = -1;
	strcpy(npcs->npcs[5].quest_id, "none");
	strcpy(dialogues[6].ids[0], "doggy");
	dialogues[6].len = 1;
	strcpy(npcs->npcs[6].id, "snoop_dogg");
	strcpy(npcs->npcs[6].name, "Calvin the Storyteller");
	strcpy(npcs->npcs[6].description,
		"A smooth-talking wanderer with a gift for verse and a knowing smile.");
	npcs->npcs[6].dialogues = dialogues[6];
	npcs->npcs[6].dialogue_index = 0;
	npcs->npcs[6].hp = 40;
	npcs->npcs[6].attack = 2;
	strcpy(npcs->npcs[6].quest_id, "none");
	strcpy(dialogues[7].ids[0], "pulpy");
	dialogues[7].len = 1;
	strcpy(npcs->npcs[7].id, "martin_scorsesse");
	strcpy(npcs->npcs[7].name, "Martin the Auteur");
	strcpy(npcs->npcs[7].description,
		"A director with a sharp suit and a sharper tongue, obsessed with detail.");
	npcs->npcs[7].dialogues = dialogues[7];
	npcs->npcs[7].dialogue_index = 0;
	npcs->npcs[7].hp = -1;
	npcs->npcs[7].attack = -1;
	strcpy(npcs->npcs[7].quest_id, "gold_rook");
	dialogues[8].len = 0;
	strcpy(npcs->npcs[8].id, "saitama");
	strcpy(npcs->npcs[8].name, "Saitama the Bored");
	strcpy(npcs->npcs[8].description, "A bald man in a plain cape, whose power is matched only by his ennui.");
	npcs->npcs[8].dialogues = dialogues[8];
	npcs->npcs[8].dialogue_index = 0;
	npcs->npcs[8].hp = 100;
	npcs->npcs[8].attack = 30;
	strcpy(npcs->npcs[8].quest_id, "none");
	strcpy(dialogues[9].ids[0], "president_dialogue0");
	strcpy(dialogues[9].ids[1], "dialogues_about_religion");
	dialogues[9].len = 2;
	strcpy(npcs->npcs[9].id, "donald_trump");
	strcpy(npcs->npcs[9].name, "The Gilded Orator");
	strcpy(npcs->npcs[9].description, "A man of wealth and bombast, standing atop the hill with a golden gaze.");
	npcs->npcs[9].dialogues = dialogues[9];
	npcs->npcs[9].dialogue_index = 0;
	npcs->npcs[9].hp = 200;
	npcs->npcs[9].attack = 10;
	strcpy(npcs->npcs[9].quest_id, "none");
	npcs->len = 10;
}

void	initialize_items(t_all_items *items)
{
	strcpy(items->items[0].id, "rook");
	strcpy(items->items[0].name, "Chess Rook");
	strcpy(items->items[0].description, "A carved stone piece, simple but formidable in the endgame.");
	items->items[0].obtainable = 1;
	items->items[0].heal = 0;
	strcpy(items->items[1].id, "heaven");
	strcpy(items->items[1].name, "Gilded Canvas");
	strcpy(items->items[1].description,
		"A masterpiece that seems to radiate light, rumored to hold a secret.");
	items->items[1].obtainable = 0;
	items->items[1].heal = 0;
	strcpy(items->items[2].id, "philosophical_stone");
	strcpy(items->items[2].name, "Philosopher's Fragment");
	strcpy(items->items[2].description,
		"A shard of a legendary artifact said to contain the essence of thought itself.");
	items->items[2].obtainable = 1;
	items->items[2].heal = 1;
	strcpy(items->items[3].id, "diamond");
	strcpy(items->items[3].name, "Uncut Diamond");
	strcpy(items->items[3].description,
		"A rough stone that catches the light with unusual brilliance.");
	items->items[3].obtainable = 1;
	items->items[3].heal = 0;
	strcpy(items->items[4].id, "gold");
	strcpy(items->items[4].name, "Gold Ingot");
	strcpy(items->items[4].description, "A heavy bar of pure gold, stamped with an ancient seal.");
	items->items[4].obtainable = 1;
	items->items[4].heal = 0;
	strcpy(items->items[5].id, "oscar");
	strcpy(items->items[5].name, "Golden Laurel");
	strcpy(items->items[5].description, "A symbol of ultimate achievement, coveted by all who seek glory.");
	items->items[5].obtainable = 0;
	items->items[5].heal = 1;
	items->len = 6;
}

void	initialize_rooms(t_all_rooms *rooms)
{
	t_list_of	exit[MAX_LEN];
	t_list_of	npcs[MAX_LEN];
	t_list_of	items[MAX_LEN];
	t_list_of	players[MAX_LEN];

	strcpy(exit[0].ids[0], "none");
	strcpy(exit[0].ids[1], "art.gallery");
	strcpy(exit[0].ids[2], "none");
	strcpy(exit[0].ids[3], "FIDE.hall");
	exit[0].len = 4;
	npcs[0].len = 0;
	items[0].len = 0;
	players[0].len = 0;
	strcpy(rooms->rooms[0].id, "start");
	strcpy(rooms->rooms[0].name, "Village_of_Ashfield");
	strcpy(rooms->rooms[0].description,
        "A quiet rural settlement at the edge of the kingdom, known for its inn and its silence.");
	rooms->rooms[0].exits = exit[0];
	rooms->rooms[0].npcs = npcs[0];
	rooms->rooms[0].items = items[0];
	rooms->rooms[0].players = players[0];
	strcpy(exit[1].ids[0], "none");
	strcpy(exit[1].ids[1], "philosophers.retreat");
	strcpy(exit[1].ids[2], "start");
	strcpy(exit[1].ids[3], "thinkers.library");
	exit[1].len = 4;
	strcpy(npcs[1].ids[0], "magnus_carlsen");
	npcs[1].len = 1;
	strcpy(items[1].ids[0], "rook");
	items[1].len = 1;
	players[1].len = 0;
	strcpy(rooms->rooms[1].id, "FIDE.hall");
	strcpy(rooms->rooms[1].name, "The Grandmaster's Chamber");
	strcpy(rooms->rooms[1].description,
		"A hall where the greatest chess minds have debated strategy for decades.");
	rooms->rooms[1].exits = exit[1];
	rooms->rooms[1].npcs = npcs[1];
	rooms->rooms[1].items = items[1];
	rooms->rooms[1].players = players[1];
	strcpy(exit[2].ids[0], "none");
	strcpy(exit[2].ids[1], "west.end");
	strcpy(exit[2].ids[2], "FIDE.hall");
	strcpy(exit[2].ids[3], "none");
	exit[2].len = 4;
	strcpy(npcs[2].ids[0], "rene_descartes");
	strcpy(npcs[2].ids[1], "charles_darwin");
	npcs[2].len = 2;
	items[2].len = 0;
	players[2].len = 0;
	strcpy(rooms->rooms[2].id, "thinkers.library");
	strcpy(rooms->rooms[2].name, "The Reading Room");
	strcpy(rooms->rooms[2].description,
		"A vast library filled with ancient texts and modern treatises on logic and nature.");
	rooms->rooms[2].exits = exit[2];
	rooms->rooms[2].npcs = npcs[2];
	rooms->rooms[2].items = items[2];
	rooms->rooms[2].players = players[2];
	strcpy(exit[3].ids[0], "start");
	strcpy(exit[3].ids[1], "cinema.house");
	strcpy(exit[3].ids[2], "none");
	strcpy(exit[3].ids[3], "philosophers.retreat");
	exit[3].len = 4;
	strcpy(npcs[3].ids[0], "pablo_picasso");
	npcs[3].len = 1;
	strcpy(items[3].ids[0], "heaven");
	items[3].len = 1;
	players[3].len = 0;
	strcpy(rooms->rooms[3].id, "art.gallery");
	strcpy(rooms->rooms[3].name, "The Starry Atelier");
	strcpy(rooms->rooms[3].description,
		"A workshop where visions of chaos and beauty have been painted into existence.");
	rooms->rooms[3].exits = exit[3];
	rooms->rooms[3].npcs = npcs[3];
	rooms->rooms[3].items = items[3];
	rooms->rooms[3].players = players[3];
	strcpy(exit[4].ids[0], "FIDE.hall");
	strcpy(exit[4].ids[1], "fiction.loft");
	strcpy(exit[4].ids[2], "art.gallery");
	strcpy(exit[4].ids[3], "west.end");
	exit[4].len = 4;
	strcpy(npcs[4].ids[0], "franz_kafka");
	strcpy(npcs[4].ids[1], "fiodor_dostoievsky");
	npcs[4].len = 2;
	items[4].len = 0;
	players[4].len = 0;
	strcpy(rooms->rooms[4].id, "philosophers.retreat");
	strcpy(rooms->rooms[4].name, "The Abyss");
	strcpy(rooms->rooms[4].description,
        "A place of deep reflection and existential anguish, where words weigh heavy.");
	rooms->rooms[4].exits = exit[4];
	rooms->rooms[4].npcs = npcs[4];
	rooms->rooms[4].items = items[4];
	rooms->rooms[4].players = players[4];
	strcpy(exit[5].ids[0], "thinkers.library");
	strcpy(exit[5].ids[1], "chapel.hill");
	strcpy(exit[5].ids[2], "philosophers.retreat");
	strcpy(exit[5].ids[3], "none");
	exit[5].len = 4;
	strcpy(npcs[5].ids[0], "snoop_dogg");
	npcs[5].len = 1;
	strcpy(items[5].ids[0], "diamond");
	items[5].len = 1;
	players[5].len = 0;
	strcpy(rooms->rooms[5].id, "west.end");
	strcpy(rooms->rooms[5].name, "The Crossroads");
	strcpy(rooms->rooms[5].description,
		"A dusty junction where travelers from all walks of life exchange stories.");
	rooms->rooms[5].exits = exit[5];
	rooms->rooms[5].npcs = npcs[5];
	rooms->rooms[5].items = items[5];
	rooms->rooms[5].players = players[5];
	strcpy(exit[6].ids[0], "art.gallery");
	strcpy(exit[6].ids[1], "none");
	strcpy(exit[6].ids[2], "none");
	strcpy(exit[6].ids[3], "fiction.loft");
	exit[6].len = 4;
	strcpy(npcs[6].ids[0], "martin_scorsesse");
	npcs[6].len = 1;
	items[6].len = 0;
	players[6].len = 0;
	strcpy(rooms->rooms[6].id, "cinema.house");
	strcpy(rooms->rooms[6].name, "The Projection Room");
	strcpy(rooms->rooms[6].description,
		"A dark room where flickering images have shaped the dreams of many.");
	rooms->rooms[6].exits = exit[6];
	rooms->rooms[6].npcs = npcs[6];
	rooms->rooms[6].items = items[6];
	rooms->rooms[6].players = players[6];
	strcpy(exit[7].ids[0], "philosophers.retreat");
	strcpy(exit[7].ids[1], "none");
	strcpy(exit[7].ids[2], "cinema.house");
	strcpy(exit[7].ids[3], "chapel.hill");
	exit[7].len = 4;
	strcpy(npcs[7].ids[0], "saitama");
	npcs[7].len = 1;
	items[7].len = 0;
	players[7].len = 0;
	strcpy(rooms->rooms[7].id, "fiction.loft");
	strcpy(rooms->rooms[7].name, "The Epicenter");
	strcpy(rooms->rooms[7].description,
		"A cluttered attic filled with comic books, myths, and tales of heroism.");
	rooms->rooms[7].exits = exit[7];
	rooms->rooms[7].npcs = npcs[7];
	rooms->rooms[7].items = items[7];
	rooms->rooms[7].players = players[7];
	strcpy(exit[8].ids[0], "west.end");
	strcpy(exit[8].ids[1], "none");
	strcpy(exit[8].ids[2], "fiction.loft");
	strcpy(exit[8].ids[3], "none");
	exit[8].len = 4;
	strcpy(npcs[8].ids[0], "donald_trump");
	npcs[8].len = 1;
	strcpy(items[8].ids[0], "gold");
	items[8].len = 1;
	players[8].len = 0;
	strcpy(rooms->rooms[8].id, "chapel.hill");
	strcpy(rooms->rooms[8].name, "The Pinnacle");
	strcpy(rooms->rooms[8].description,
		"A windswept hilltop overlooking the kingdom, often visited by the powerful.");
	rooms->rooms[8].exits = exit[8];
	rooms->rooms[8].npcs = npcs[8];
	rooms->rooms[8].items = items[8];
	rooms->rooms[8].players = players[8];
	rooms->len = 9;
}

void	initialize_world(t_world *world)
{
	t_all_groups	groups;
	t_all_dialogues	dialogues;
	t_all_missions	missions;
	t_all_quests	quests;
	t_all_npcs		npcs;
	t_all_items		items;
	t_all_rooms		rooms;

	initialize_groups(&groups);
	initialize_dialogue(&dialogues);
	initialize_missions(&missions);
	initialize_quests(&quests);
	initialize_npcs(&npcs);
	initialize_items(&items);
	initialize_rooms(&rooms);
	world->groups = groups;
	world->dialogues = dialogues;
	world->missions = missions;
	world->quests = quests;
	world->npcs = npcs;
	world->items = items;
	world->rooms = rooms;
}
