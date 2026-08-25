#include <stdio.h>

typedef struct
{
    int id;
} player;

typedef struct
{
    int chose;
    player players[128];
} ensemble;

int main()
{
    ensemble e;
    e.chose = 3;
    printf("e.chose=%d\n",e.chose);
    printf("e.player=%d\n",e.players[0].id); // non-initialisé = choses aleatoires
    return (0);
}
