/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtome-ve <gtome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:24:39 by gtome-ve          #+#    #+#             */
/*   Updated: 2025/08/19 21:54:31 by gtome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	count_elements(t_game *game, int i, int j)
{
	char	c;

	c = game->map.grid[i][j];
	if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
	{
		ft_printf("Error: Invalid char");
		free_game(game);
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
			ft_printf("Error: Multiple players in map\n");
			free_game(game);
			exit(1);
		}
		game->map.player_x = j;
		game->map.player_y = i;
	}
}

static void	validate_elements(t_game *game)
{
	if (game->map.collectibles < 1)
	{
		ft_printf("Error: At least one collectible required\n");
		free_game(game);
		exit(1);
	}
	if (game->map.exit != 1)
	{
		ft_printf("Error: Exactly one exit required\n");
		free_game(game);
		exit(1);
	}
	if (game->map.player_x == -1)
	{
		ft_printf("Error: Exactly one player required\n");
		free_game(game);
		exit(1);
	}
}

void	check_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->map.collectibles = 0;
	game->map.exit = 0;
	game->map.player_x = -1;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.cols)
		{
			count_elements(game, i, j);
			j++;
		}
		i++;
	}
	validate_elements(game);
}

void	check_retangular(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		if (ft_strlen(game->map.grid[i]) != (size_t)game->map.cols)
		{
			ft_printf("Error: Map is not rectangular at row %d\n", i);
			free_game(game);
			exit(1);
		}
		i++;
	}
}

void	check_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.cols && i < game->map.rows)
	{
		if (game->map.grid[0][i] != '1'
			|| game->map.grid[game->map.rows - 1][i] != '1')
		{
			ft_printf("Error: Map must be surrounded by walls\n");
			free_game(game);
			exit(1);
		}
		if (game->map.grid[i][0] != '1'
			|| game->map.grid[i][game->map.cols - 1] != '1')
		{
			ft_printf("Error: Map must be surrounded by walls\n");
			free_game(game);
			exit(1);
		}
		i++;
	}
}
