/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 00:03:33 by Alfofern          #+#    #+#             */
/*   Updated: 2022/12/22 10:26:47 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	f;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	f = ft_strlen(s1) - 1;
	while (s1[f] && ft_strchr(set, s1[f]))
		f--;
	return (ft_substr(s1, 0, f + 1));
}
