
#include "so_long.h"

void free_map(t_game *game)
{
    int i = 0;
    while (i < game->map.rows)
    {
        free(game->map.grid[i]);
        game->map.grid[i] = NULL; // Nullify each row
        i++;
    }
    free(game->map.grid);
    game->map.grid = NULL; // Nullify grid
    game->map.rows = 0; // Reset rows
    game->map.cols = 0; // Reset cols
}

void free_sprites(t_game *game)
{
    if (game->sprites.wall)
    {
        mlx_destroy_image(game->mlx, game->sprites.wall);
        game->sprites.wall = NULL; // Nullify
    }
    if (game->sprites.floor)
    {
        mlx_destroy_image(game->mlx, game->sprites.floor);
        game->sprites.floor = NULL; // Nullify
    }
    if (game->sprites.player)
    {
        mlx_destroy_image(game->mlx, game->sprites.player);
        game->sprites.player = NULL; // Nullify
    }
    if (game->sprites.collectible)
    {
        mlx_destroy_image(game->mlx, game->sprites.collectible);
        game->sprites.collectible = NULL; // Nullify
    }
    if (game->sprites.exit)
    {
        mlx_destroy_image(game->mlx, game->sprites.exit);
        game->sprites.exit = NULL; // Nullify
    }
}

void free_game(t_game *game)
{
    if (game->map.grid)
        free_map(game);
    if (game->sprites.wall || game->sprites.floor || game->sprites.player ||
        game->sprites.collectible || game->sprites.exit)
        free_sprites(game);
    if (game->window)
    {
        mlx_destroy_window(game->mlx, game->window);
        game->window = NULL; // Nullify
    }
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        game->mlx = NULL; // Nullify
    }
}
