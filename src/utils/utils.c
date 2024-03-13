/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:29:44 by alfofern          #+#    #+#             */
/*   Updated: 2024/02/11 19:30:21 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	avoid_if_is_last(char *s, int *i)
{
	int	k;

	k = *i;
	while (s[k] == ' ')
		k++;
	if (s[k] == '\n')
		*i = k;
	return (0);
}

char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

void	*ft_freenull(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

char	*ft_free_join(char *s1, char *s2, int strtofree)
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
	dest[i] = '\0';
	if (strtofree == 1)
		free(s1);
	else if (strtofree == 2)
		free(s2);
	else if (strtofree == 3)
	{
		ft_freenull(s1);
		ft_freenull(s2);
	}
	return (dest);
}

int	ft_err_msg(char *str1, char *str2, char *str3, int ernb)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putendl_fd(str3, STDERR_FILENO);
	return (ernb);
}
