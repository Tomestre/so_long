/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtome-ve <gtome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:24:22 by gtome-ve          #+#    #+#             */
/*   Updated: 2025/08/19 21:08:04 by gtome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

void	validate_map(t_game *game)
{
	check_characters(game);
	check_retangular(game);
	check_walls(game);
	check_path(game);
}

static void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("Error initializing MLX\n");
		free_game(game);
		exit(1);
	}
	game->window = mlx_new_window(game->mlx, game->map.cols * 32,
			game->map.rows * 32, "So Long");
	if (!game->window)
	{
		ft_printf("Error creating window\n");
		free_game(game);
		exit(1);
	}
	load_sprites(game);
	render_map(game);
	mlx_key_hook(game->window, key_hook, game);
	mlx_hook(game->window, 17, 0, close_window, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game = (t_game){0};
	if (argc != 2)
	{
		write(2, "Usage: ./so_long <map_file>\n", 28);
		return (1);
	}
	read_map(argv[1], &game);
	validate_map(&game);
	init_game(&game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
