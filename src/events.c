/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtome-ve <gtome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:34:49 by gtome-ve          #+#    #+#             */
/*   Updated: 2025/08/19 20:58:01 by gtome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_collectible(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->map.grid[new_y][new_x] = '0';
		game->map.collectibles--;
	}
}

static void	check_exit(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[new_y][new_x] == 'E' && game->map.collectibles == 0)
	{
		printf("Jogo concluído com %d movimentos!\n", game->moves + 1);
		free_game(game);
		exit(0);
	}
	else if (game->map.grid[new_y][new_x] == 'E')
	{
		game->map.tile = 'E';
	}
}

static void	update_position(t_game *game, int new_x, int new_y)
{
	game->map.grid[game->map.player_y][game->map.player_x] = '0';
	if (game->map.tile == 'E' && (game->map.grid[new_y][new_x] == '0'
		|| game->map.grid[new_y][new_x] == 'C'))
	{
		game->map.grid[game->map.player_y][game->map.player_x] = 'E';
		game->map.tile = 'L';
	}
	game->map.grid[new_y][new_x] = 'P';
	game->map.player_x = new_x;
	game->map.player_y = new_y;
	game->moves++;
	printf("Movimentos: %d\n", game->moves);
	render_map(game);
}

static void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player_x + dx;
	new_y = game->map.player_y + dy;
	if (new_x < 0 || new_x >= game->map.cols || new_y < 0
		|| new_y >= game->map.rows)
		return ;
	if (game->map.grid[new_y][new_x] == '1')
		return ;
	update_collectible(game, new_x, new_y);
	check_exit(game, new_x, new_y);
	update_position(game, new_x, new_y);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		free_game(game);
		exit(0);
	}
	else if (keycode == 119 || keycode == 65362)
		move_player(game, 0, -1);
	else if (keycode == 115 || keycode == 65364)
		move_player(game, 0, 1);
	else if (keycode == 97 || keycode == 65361)
		move_player(game, -1, 0);
	else if (keycode == 100 || keycode == 65363)
		move_player(game, 1, 0);
	return (0);
}
