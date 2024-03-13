/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:50:18 by alfofern          #+#    #+#             */
/*   Updated: 2022/12/22 10:27:06 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*dest;
	size_t		i;
	size_t		j;

	dest = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	j = 0;
	if (dest)
	{
		while (s1[i] != '\0')
		{
			dest[i] = s1[i];
			i++;
		}
		while (s2[j] != '\0')
		{
			dest[i] = s2[j];
			j++;
			i++;
		}
		dest[i] = '\0';
	}
	else
		return (NULL);
	return (dest);
}
