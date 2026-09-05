#include "yaml.h"
#include "../world.h"

t_line_type generate_line_type(int level, char *key, int needs_arg, char *type)
{
    t_line_type result;

    result.level = level;
    strcpy(result.key, key);
    result.needs_arg = needs_arg;
    strcpy(result.type, type);
    return (result);
}

int infinite_loop(FILE *f, char *result)
{
    while (fgets(result, sizeof(result), f))
    {
        
    }
}

void load_world(const char *path)
{
    FILE *f;
    char result[BUFFER_SIZE];

    f = fopen(path, "r");
    if (!f)
    {
        printf("error while loading the 'world.yaml' file");
        exit(0);
    }
    infinite_loop(f, result);
}
