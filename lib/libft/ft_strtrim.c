/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtome-ve <gtome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:19:58 by gtome-ve          #+#    #+#             */
/*   Updated: 2024/12/08 18:55:50 by gtome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	cont_s1;

	if (!s1 || !set)
		return (NULL);
	cont_s1 = ft_strlen(s1);
	while (*s1 && ft_strchr(set, *s1))
	{
		s1++;
		cont_s1--;
	}
	while (cont_s1 && ft_strchr(set, s1[cont_s1 - 1]))
	{
		cont_s1--;
	}
	ret = (char *)malloc(cont_s1 + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, cont_s1 + 1);
	ret[cont_s1] = '\0';
	return (ret);
}
