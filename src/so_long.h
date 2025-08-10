#ifndef SO_LONG_H
#define SO_LONG_H

#include "lib/mlx.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct s_map
{
	char **grid;
	int rows;
	int cols;
	int player_x;
	int player_y;
	int collectibles;
	int exit;
} t_map;

typedef struct s_sprites
{
    void *wall;
    void *floor;
    void *player;
    void *collectible;
    void *exit;
} t_sprites;

typedef struct s_game
{
	void *mlx;
	void *window;
	void *img;
	t_map map;
	t_sprites sprites;
    int moves;
} t_game;

void load_sprites(t_game *game);
void render_map(t_game *game);
void read_map(const char *file_path, t_game *game);
void validate_map(t_game *game);
void free_map(t_game *game);
int key_hook(int keycode, t_game *game);
void check_path(t_game *game);
#endif
