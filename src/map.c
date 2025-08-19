/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtome-ve <gtome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:24:46 by gtome-ve          #+#    #+#             */
/*   Updated: 2025/08/19 21:56:40 by gtome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(const char *content)
{
	int			lines;
	const char	*ptr;

	ptr = content;
	lines = 0;
	while (*ptr)
	{
		if (*ptr == '\n')
			lines++;
		ptr++;
	}
	if (ptr > content && *(ptr - 1) != '\n')
		lines++;
	return (lines);
}
