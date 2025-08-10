// src/render.c
#include "so_long.h"

void load_sprites(t_game *game)
{
    int width = 32;
    int height = 32;
    game->sprites.wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &width, &height);
    game->sprites.floor = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", &width, &height);
    game->sprites.player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &width, &height);
    game->sprites.collectible = mlx_xpm_file_to_image(game->mlx, "textures/collectible.xpm", &width, &height);
    game->sprites.exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &width, &height);
    // Verifique se carregou (adicione erros se necessário)
}

void render_map(t_game *game)
{
    int y = 0;
    while (y < game->map.rows)
    {
        int x = 0;
        while (x < game->map.cols)
        {
            void *img;
            if (game->map.grid[y][x] == '1')
                img = game->sprites.wall;
            else if (game->map.grid[y][x] == '0')
                img = game->sprites.floor;
            else if (game->map.grid[y][x] == 'P')
                img = game->sprites.player;
            else if (game->map.grid[y][x] == 'C')
                img = game->sprites.collectible;
            else if (game->map.grid[y][x] == 'E')
                img = game->sprites.exit;
            else
                img = game->sprites.floor; // Default
            mlx_put_image_to_window(game->mlx, game->window, img, x * 32, y * 32);
            x++;
        }
        y++;
    }
}
