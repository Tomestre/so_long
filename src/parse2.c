#include "so_long.h"

static void flood_fill(t_game *game, int x, int y, char **visited)
{
    if (x < 0 || x >= game->map.cols || y < 0 || y >= game->map.rows)
        return;
    if (game->map.grid[y][x] == '1' || visited[y][x] == '1')
        return;
    visited[y][x] = '1'; // Marca como visitado
    flood_fill(game, x - 1, y, visited); // Esquerda
    flood_fill(game, x + 1, y, visited); // Direita
    flood_fill(game, x, y - 1, visited); // Cima
    flood_fill(game, x, y + 1, visited); // Baixo
}

void check_path(t_game *game)
{
    // Cria uma cópia do mapa para visitas
    char **visited = malloc(sizeof(char *) * game->map.rows);
    int i = 0;
    while (i < game->map.rows)
    {
        visited[i] = malloc(game->map.cols + 1);
        memset(visited[i], '0', game->map.cols + 1);
        i++;
    }

    // Inicia flood fill da posição do jogador
    flood_fill(game, game->map.player_x, game->map.player_y, visited);

    // Verifica se todos 'C' e 'E' foram alcançados
    i = 0;
    while (i < game->map.rows)
    {
        int j = 0;
        while (j < game->map.cols)
        {
            if ((game->map.grid[i][j] == 'C' || game->map.grid[i][j] == 'E') && visited[i][j] == '0')
            {
                fprintf(stderr, "Error: No valid path to all collectibles/exit\n");
                int k = 0;
                while (k < game->map.rows)
                {
                    free(visited[k]);
                    k++;
                }
                free(visited);
                exit(1);
            }
            j++;
        }
        i++;
    }

    // Libera memória
    i = 0;
    while (i < game->map.rows)
    {
        free(visited[i]);
        i++;
    }
    free(visited);
}
