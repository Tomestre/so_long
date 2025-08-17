#include "so_long.h"

static void flood_fill(t_game *game, int x, int y, char **visited)
{
    if (x < 0 || x >= game->map.cols || y < 0 || y >= game->map.rows)
        return;
    if (game->map.grid[y][x] == '1' || visited[y][x] == '1')
        return;
    visited[y][x] = '1';
    flood_fill(game, x - 1, y, visited);
    flood_fill(game, x + 1, y, visited);
    flood_fill(game, x, y - 1, visited);
    flood_fill(game, x, y + 1, visited);
}

static char **allocate_visited(t_game *game)
{
    char **visited;
    int i = 0;

    visited = malloc(sizeof(char *) * game->map.rows);
    if (!visited)
    {
        ft_printf("Error: Failed to allocate visited array\n");
        free_game(game); // Clean up
        exit(1);
    }
    while (i < game->map.rows)
    {
        visited[i] = malloc(game->map.cols + 1);
        if (!visited[i])
        {
            while (i > 0)
                free(visited[--i]);
            free(visited);
            ft_printf("Error: Failed to allocate visited row\n");
            free_game(game); // Clean up
            exit(1);
        }
        ft_memset(visited[i], '0', game->map.cols + 1);
        i++;
    }
    return (visited);
}
static void free_visited(char **visited, int rows)
{
    int i = 0;
    while (i < rows)
    {
        free(visited[i]);
        i++;
    }
    free(visited);
}

static void check_visited(t_game *game, char **visited)
{
    int i = 0;
    while (i < game->map.rows)
    {
        int j = 0;
        while (j < game->map.cols)
        {
            if ((game->map.grid[i][j] == 'C' || game->map.grid[i][j] == 'E')
                && visited[i][j] == '0')
            {
                ft_printf("Error: No valid path to all collectibles/exit\n");
                free_visited(visited, game->map.rows); // Free visited
                free_game(game); // Clean up game
                exit(1);
            }
            j++;
        }
        i++;
    }
}

void check_path(t_game *game)
{
    char **visited = allocate_visited(game);
    flood_fill(game, game->map.player_x, game->map.player_y, visited);
    check_visited(game, visited);
    free_visited(visited, game->map.rows);
}
