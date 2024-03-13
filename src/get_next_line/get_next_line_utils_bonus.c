/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:04:42 by Alfofern          #+#    #+#             */
/*   Updated: 2023/02/06 18:46:29 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s || s[0] == 0)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_calloc(size_t count, size_t size)
{
	char	*a;
	size_t	i;

	i = 0;
	a = malloc(count * size);
	if (a == NULL)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		a[i] = 0;
		i++;
	}
	return (a);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*dest;
	size_t		i;
	size_t		j;

	if (!s1)
		s1 = ft_calloc(1, 1);
	dest = (char *)ft_calloc(((ft_strlen(s1) + ft_strlen(s2) + 1)), 1);
	i = 0;
	j = 0;
	if (dest)
	{
		while (s1[i] != '\0')
			dest[i++] = s1[j++];
		j = 0;
		while (s2[j] != '\0')
			dest[i++] = s2[j++];
	}
	else
		return (NULL);
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
