/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:03:09 by alfofern          #+#    #+#             */
/*   Updated: 2022/12/22 10:27:04 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	x;

	x = ft_strlen(src) + ft_strlen(dst);
	if (dstsize <= ft_strlen(dst))
		return ((ft_strlen(src) + dstsize));
	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while ((src[j]) && (i < dstsize -1))
	{
		(dst[i] = src[j]);
		i++;
		j++;
	}
	dst[i] = '\0';
	return (x);
}
