#include "so_long.h"

// src/parse.c
static void check_characters(t_game *game)
{
    int i = 0, j;
    game->map.collectibles = 0;
    game->map.exit = 0;
    game->map.player_x = -1;

    while (i < game->map.rows)
    {
        j = 0;
        printf("Processing Row %d: %s\n", i, game->map.grid[i]); // Debug print
        while (j < game->map.cols)
        {
            char c = game->map.grid[i][j];
            printf("  Col %d: '%c' (ASCII %d)\n", j, c, c); // Debug character
            if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
            {
                fprintf(stderr, "Error: Invalid character '%c' (ASCII %d) at position (%d, %d)\n", c, c, j, i);
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
                    fprintf(stderr, "Error: Multiple players in map\n");
                    exit(1);
                }
                game->map.player_x = j;
                game->map.player_y = i;
            }
            j++;
        }
        i++;
    }

    if (game->map.collectibles < 1)
    {
        fprintf(stderr, "Error: At least one collectible required\n");
        exit(1);
    }
    if (game->map.exit != 1)
    {
        fprintf(stderr, "Error: Exactly one exit required\n");
        exit(1);
    }
    if (game->map.player_x == -1)
    {
        fprintf(stderr, "Error: Exactly one player required\n");
        exit(1);
    }
}

static void check_retangular(t_game *game)
{
	int i;

	i = 0;
	while(i < game->map.rows)
	{
		if (strlen(game->map.grid[i]) != (size_t)game->map.cols)
		{
			fprintf(stderr, "Error: Map is not rectangular at row %d\n", i);
			exit(1);
		}
		i++;
	}
}

static void check_walls(t_game *game)
{
	int i;

	i = 0;
	while(i < game->map.cols)
	{
		if (game->map.grid[0][i] != '1' || game->map.grid[game->map.rows - 1][i] != '1')
		{
			fprintf(stderr, "Error: Map must be surrounded by walls\n");
			exit(1);
		}
		i++;
	}
	i = 0;
	while(i < game->map.rows)
	{
		if (game->map.grid[i][0] != '1' || game->map.grid[i][game->map.cols - 1] != '1')
		{
			fprintf(stderr, "Error: Map must be surrounded by walls\n");
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
