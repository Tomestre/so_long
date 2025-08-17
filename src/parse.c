#include "so_long.h"

static void count_elements(t_game *game, int i, int j)
{
    char c = game->map.grid[i][j];
    ft_printf("  Col %d: '%c' (ASCII %d)\n", j, c, c);
    if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
    {
        ft_printf("Error: Invalid character '%c' (ASCII %d) at position (%d, %d)\n",
                c, c, j, i);
        free_game(game); // Clean up
        exit(1);
    }
    if (c == 'C')
        game->map.collectibles++;
    if (c == 'E')
        game->map.exit++;
    if (c == 'P')
    {
        if (game->map.player_x != -1)
        {
            ft_printf("Error: Multiple players in map\n");
            free_game(game); // Clean up
            exit(1);
        }
        game->map.player_x = j;
        game->map.player_y = i;
    }
}

static void check_characters(t_game *game)
{
    int i = 0;
    game->map.collectibles = 0;
    game->map.exit = 0;
    game->map.player_x = -1;
    while (i < game->map.rows)
    {
        int j = 0;
        ft_printf("Processing Row %d: %s\n", i, game->map.grid[i]);
        while (j < game->map.cols)
        {
            count_elements(game, i, j);
            j++;
        }
        i++;
    }
    if (game->map.collectibles < 1)
    {
        ft_printf("Error: At least one collectible required\n");
        free_game(game); // Clean up
        exit(1);
    }
    if (game->map.exit != 1)
    {
        ft_printf("Error: Exactly one exit required\n");
        free_game(game); // Clean up
        exit(1);
    }
    if (game->map.player_x == -1)
    {
        ft_printf("Error: Exactly one player required\n");
        free_game(game); // Clean up
        exit(1);
    }
}

static void check_retangular(t_game *game)
{
    int i = 0;
    while (i < game->map.rows)
    {
        if (ft_strlen(game->map.grid[i]) != (size_t)game->map.cols)
        {
            ft_printf("Error: Map is not rectangular at row %d\n", i);
            free_game(game); // Clean up
            exit(1);
        }
        i++;
    }
}

static void check_walls(t_game *game)
{
    int i = 0;
    while (i < game->map.cols)
    {
        if (game->map.grid[0][i] != '1' || game->map.grid[game->map.rows - 1][i] != '1')
        {
            ft_printf("Error: Map must be surrounded by walls\n");
            free_game(game); // Clean up
            exit(1);
        }
        i++;
    }
    i = 0;
    while (i < game->map.rows)
    {
        if (game->map.grid[i][0] != '1' || game->map.grid[i][game->map.cols - 1] != '1')
        {
            ft_printf("Error: Map must be surrounded by walls\n");
            free_game(game); // Clean up
            exit(1);
        }
        i++;
    }
}

void validate_map(t_game *game)
{
    check_characters(game);
    check_retangular(game);
    check_walls(game);
    check_path(game);
}
