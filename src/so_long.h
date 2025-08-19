/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtome-ve <gtome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:08:45 by gtome-ve          #+#    #+#             */
/*   Updated: 2025/08/19 22:12:47 by gtome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "mlx.h"

typedef struct s_sprites
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectible;
	void	*exit;
}	t_sprites;

typedef struct s_map
{
	char	**grid;
	int		rows;
	int		cols;
	int		collectibles;
	int		exit;
	int		player_x;
	int		player_y;
	char	tile;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_sprites	sprites;
	int			moves;
}	t_game;

void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
void	ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strstr(const char *haystack, const char *needle);
void	ft_printf(const char *format, ...);
void	read_map(const char *file_path, t_game *game);
int		count_lines(const char *content);
void	free_map(t_game *game);
void	free_sprites(t_game *game);
void	free_game(t_game *game);
void	validate_map(t_game *game);
void	load_sprites(t_game *game);
void	render_map(t_game *game);
int		key_hook(int keycode, t_game *game);
int		close_window(t_game *game);
char	*read_file(const char *file_path);
size_t	get_file_size(int fd);
char	*read_file_content(int fd, size_t size);
void	check_characters(t_game *game);
void	check_retangular(t_game *game);
void	check_walls(t_game *game);
void	check_path(t_game *game);

#endif