/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtome-ve <gtome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:24:58 by gtome-ve          #+#    #+#             */
/*   Updated: 2025/08/19 22:22:24 by gtome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_sprites(t_game *game)
{
	int	width;
	int	height;

	width = 32;
	height = 32;
	game->sprites.wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &width, &height);
	game->sprites.floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &width, &height);
	game->sprites.player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &width, &height);
	game->sprites.collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &width, &height);
	game->sprites.exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", &width, &height);
}

static void	*get_sprite(t_game *game, char c)
{
	if (c == '1')
		return (game->sprites.wall);
	else if (c == '0')
		return (game->sprites.floor);
	else if (c == 'P')
		return (game->sprites.player);
	else if (c == 'C')
		return (game->sprites.collectible);
	else if (c == 'E')
		return (game->sprites.exit);
	else
		return (game->sprites.floor);
}

void	render_map(t_game *game)
{
	int		y;
	int		x;
	void	*img;

	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.cols)
		{
			img = get_sprite(game, game->map.grid[y][x]);
			mlx_put_image_to_window(game->mlx,
				game->window, img, x * 32, y * 32);
			x++;
		}
		y++;
	}
}
