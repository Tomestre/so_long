/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtome-ve <gtome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:40:59 by gtome-ve          #+#    #+#             */
/*   Updated: 2025/08/19 22:14:06 by gtome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		free(game->map.grid[i]);
		game->map.grid[i] = NULL;
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
	game->map.rows = 0;
	game->map.cols = 0;
}

void	free_sprites(t_game *game)
{
	if (game->sprites.wall)
	{
		mlx_destroy_image(game->mlx, game->sprites.wall);
		game->sprites.wall = NULL;
	}
	if (game->sprites.floor)
	{
		mlx_destroy_image(game->mlx, game->sprites.floor);
		game->sprites.floor = NULL;
	}
	if (game->sprites.player)
	{
		mlx_destroy_image(game->mlx, game->sprites.player);
		game->sprites.player = NULL;
	}
	if (game->sprites.collectible)
	{
		mlx_destroy_image(game->mlx, game->sprites.collectible);
		game->sprites.collectible = NULL;
	}
	if (game->sprites.exit)
	{
		mlx_destroy_image(game->mlx, game->sprites.exit);
		game->sprites.exit = NULL;
	}
}

void	free_game(t_game *game)
{
	if (game->map.grid)
		free_map(game);
	if (game->sprites.wall || game->sprites.floor || game->sprites.player
		|| game->sprites.collectible || game->sprites.exit)
		free_sprites(game);
	if (game->window)
	{
		mlx_destroy_window(game->mlx, game->window);
		game->window = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}
