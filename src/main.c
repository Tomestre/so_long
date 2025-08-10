#include "lib/mlx.h"
#include "so_long.h"

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
        fprintf(stderr, "Error initializing MLX\n");
        free_map(&game);
        return (1);
    }
    game.window = mlx_new_window(game.mlx, game.map.cols * 32, game.map.rows * 32, "So Long");
    if (!game.window)
    {
        fprintf(stderr, "Error creating window\n");
        free_map(&game);
        return (1);
    }
    load_sprites(&game);
    render_map(&game);
    mlx_key_hook(game.window, key_hook, &game);
    mlx_loop(game.mlx);
    free_map(&game);
    return (0);
}
