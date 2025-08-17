#include "so_long.h"

int close_window(t_game *game)
{
    free_game(game); // Clean up all resources
    exit(0);
    return (0);
}

int main(int argc, char **argv)
{
    t_game game = {0};
    if (argc != 2)
    {
        write(2, "Usage: ./so_long <map_file>\n", 28);
        return (1);
    }
    read_map(argv[1], &game);
    validate_map(&game);

    game.mlx = mlx_init();
    if (!game.mlx)
    {
        ft_printf("Error initializing MLX\n");
        free_game(&game); // Use free_game instead of free_map
        return (1);
    }
    game.window = mlx_new_window(game.mlx, game.map.cols * 32, game.map.rows * 32, "So Long");
    if (!game.window)
    {
        ft_printf("Error creating window\n");
        free_game(&game); // Use free_game instead of free_map
        return (1);
    }
    load_sprites(&game);
    render_map(&game);
    mlx_key_hook(game.window, key_hook, &game);
    mlx_hook(game.window, 17, 0, close_window, &game); // Hook for window close (event 17)
    mlx_loop(game.mlx);
    free_game(&game); // Ensure cleanup after mlx_loop (though typically unreachable)
    return (0);
}
