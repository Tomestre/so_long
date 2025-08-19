/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtome-ve <gtome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:24:32 by gtome-ve          #+#    #+#             */
/*   Updated: 2025/08/19 22:45:53 by gtome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**allocate_grid(int rows)
{
	char	**grid;

	if (rows == 0)
	{
		ft_printf("Error: No lines in map\n");
		exit(1);
	}
	grid = malloc(sizeof(char *) * (rows + 1));
	if (!grid)
	{
		perror("Error allocating grid");
		exit(1);
	}
	return (grid);
}

static size_t	get_line_length(const char *line)
{
	const char	*next_line;
	size_t		len;

	next_line = ft_strchr(line, '\n');
	if (next_line)
	{
		len = next_line - line;
		if (len > 0 && line[len - 1] == '\r')
			len--;
	}
	else
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\r')
			len--;
	}
	return (len);
}

static void	split_line(const char *line, char **grid, int i)
{
	size_t	len;

	len = get_line_length(line);
	grid[i] = malloc(len + 1);
	if (!grid[i])
	{
		while (i > 0)
			free(grid[--i]);
		free(grid);
		perror("Error allocating line");
		exit(1);
	}
	ft_strncpy(grid[i], line, len);
	grid[i][len] = '\0';
}

static char	**split_map(const char *content, int rows)
{
	char		**grid;
	int			i;
	const char	*line;
	const char	*next_line;

	grid = allocate_grid(rows);
	i = 0;
	line = content;
	while (i < rows)
	{
		split_line(line, grid, i);
		next_line = ft_strchr(line, '\n');
		if (next_line)
			line = next_line + 1;
		else
			line = line + ft_strlen(line);
		i++;
	}
	grid[rows] = NULL;
	return (grid);
}

void	read_map(const char *file_path, t_game *game)
{
	char	*content;

	if (!ft_strstr(file_path, ".ber"))
	{
		ft_printf("Error: File must have .ber extension\n");
		exit(1);
	}
	content = read_file(file_path);
	game->map.rows = count_lines(content);
	if (!game->map.rows)
	{
		free(content);
		ft_printf("Error: Empty map file\n");
		free_game(game);
		exit(1);
	}
	game->map.grid = split_map(content, game->map.rows);
	game->map.cols = ft_strlen(game->map.grid[0]);
	if (!game->map.cols)
	{
		free_game(game);
		ft_printf("Error: Empty map row\n");
		exit(1);
	}
	free(content);
}
