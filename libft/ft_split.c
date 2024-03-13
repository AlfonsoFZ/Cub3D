/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:24:17 by alfofern          #+#    #+#             */
/*   Updated: 2022/12/22 10:22:19 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_stringscounter(char const *s, char d)
{
	int	counter;
	int	check;
	int	i;

	check = 1;
	counter = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == d && check == 0) || (s[i] != d && s[(i + 1)] == 0))
		{
			check = 1;
			counter ++;
		}
		else if (s[i] != d && check == 1)
			check = 0;
		i++;
	}
	return (counter);
}

static void	ft_free(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}

static size_t	ft_strlenc(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_createstrings(char *s, char c, char **res)
{
	size_t	t;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			t = ft_strlenc (&s[i], c);
			res[j++] = ft_substr(&s[i], 0, t);
			i = i + t;
			if (!res[j - 1])
			{
				ft_free(res);
				return (NULL);
			}
		}
		else
			i++;
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	res = malloc(sizeof(char *) * (ft_stringscounter(s, c) + 1));
	if (res == NULL)
		return (0);
	return (ft_createstrings((char *)s, c, res));
}
