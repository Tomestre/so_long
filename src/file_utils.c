/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtome-ve <gtome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:24:16 by gtome-ve          #+#    #+#             */
/*   Updated: 2025/08/19 21:02:29 by gtome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	get_file_size(int fd)
{
	char	buffer[1024];
	size_t	total_size;
	ssize_t	bytes_read;

	total_size = 0;
	while (1)
	{
		bytes_read = read(fd, buffer, 1024);
		if (bytes_read < 0)
		{
			perror("Error reading file size");
			exit(1);
		}
		if (bytes_read == 0)
			break ;
		total_size += bytes_read;
	}
	return (total_size);
}

static int	open_file(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	return (fd);
}

static void	validate_file_size(int fd, size_t *size)
{
	*size = get_file_size(fd);
	if (*size == 0)
	{
		close(fd);
		ft_printf("Error: Empty file\n");
		exit(1);
	}
}

char	*read_file(const char *file_path)
{
	int		fd;
	size_t	size;
	char	*buffer;

	fd = open_file(file_path);
	validate_file_size(fd, &size);
	close(fd);
	fd = open_file(file_path);
	buffer = read_file_content(fd, size);
	return (buffer);
}

char	*read_file_content(int fd, size_t size)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(size + 1);
	if (!buffer)
	{
		close(fd);
		perror("Error allocating memory");
		exit(1);
	}
	bytes_read = read(fd, buffer, size);
	if (bytes_read < 0 || (size_t)bytes_read != size)
	{
		free(buffer);
		close(fd);
		ft_printf("Error: Failed to read bytes from file\n");
		exit(1);
	}
	buffer[bytes_read] = '\0';
	close(fd);
	return (buffer);
}
