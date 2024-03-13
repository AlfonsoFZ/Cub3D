/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:48:43 by alfofern          #+#    #+#             */
/*   Updated: 2022/12/22 10:22:25 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	if ((char)c == '\0')
		return (&str[ft_strlen(str)]);
	while (str[i])
	{
		if (str[i] == (char)c)
			return (&str[i]);
		else
			i++;
	}
	return (NULL);
}
