/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:04:42 by Alfofern          #+#    #+#             */
/*   Updated: 2023/02/06 17:26:19 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char		*dest;
	size_t		i;
	size_t		j;

	if (!s1)
		s1 = ft_calloc(1, 1);
	dest = (char *)ft_calloc(((ft_strlen(s1) + ft_strlen(s2) + 1)), 1);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		dest[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		dest[i++] = s2[j++];
	free(s1);
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	if ((char)c == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == (char)c)
			return (&str[i]);
		else
			i++;
	}
	return (NULL);
}
