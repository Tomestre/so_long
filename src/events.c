// src/events.c
#include "so_long.h"

static void move_player(t_game *game, int dx, int dy)
{
    int new_x = game->map.player_x + dx;
    int new_y = game->map.player_y + dy;
    if (new_x < 0 || new_x >= game->map.cols || new_y < 0 || new_y >= game->map.rows)
        return;
    if (game->map.grid[new_y][new_x] == '1')
        return;
    if (game->map.grid[new_y][new_x] == 'C')
    {
        game->map.grid[new_y][new_x] = '0'; // Coleta
        game->map.collectibles--;
    }
    if (game->map.grid[new_y][new_x] == 'E' && game->map.collectibles == 0)
    {
        printf("Jogo concluído com %d movimentos!\n", game->moves + 1);
        exit(0); // Sai limpo
    }
    else if (game->map.grid[new_y][new_x] == 'E')
        return; // Não sai se coletáveis restantes
    // Move jogador
    game->map.grid[game->map.player_y][game->map.player_x] = '0';
    game->map.player_x = new_x;
    game->map.player_y = new_y;
    game->map.grid[new_y][new_x] = 'P';
    game->moves++;
    printf("Movimentos: %d\n", game->moves);
    render_map(game); // Re-renderiza
}

int key_hook(int keycode, t_game *game)
{
    if (keycode == 65307) // ESC
        exit(0);
    else if (keycode == 119 || keycode == 65362) // W ou Seta Cima
        move_player(game, 0, -1);
    else if (keycode == 115 || keycode == 65364) // S ou Seta Baixo
        move_player(game, 0, 1);
    else if (keycode == 97 || keycode == 65361) // A ou Seta Esquerda
        move_player(game, -1, 0);
    else if (keycode == 100 || keycode == 65363) // D ou Seta Direita
        move_player(game, 1, 0);
    return (0);
}
