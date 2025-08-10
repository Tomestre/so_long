#include "so_long.h"

void free_map(t_game *game)
{
    int i = 0;
    while (i < game->map.rows)
    {
        free(game->map.grid[i]);
        i++;
    }
    free(game->map.grid);
}
