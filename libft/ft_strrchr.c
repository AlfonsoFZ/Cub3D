/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:48:43 by alfofern          #+#    #+#             */
/*   Updated: 2022/12/22 10:26:50 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = ft_strlen(str) - 1;
	if ((char)c == '\0')
		return (&str[ft_strlen(str)]);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return (&str[i]);
		else
			i--;
	}
	return (NULL);
}
