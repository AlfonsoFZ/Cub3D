/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:54:50 by alfofern          #+#    #+#             */
/*   Updated: 2022/12/22 10:37:12 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numberofchar(long n)
{
	size_t	t;

	t = 0;
	if (n <= 0)
	{
		n = n * -1;
		t++;
	}
	while (n > 0)
	{
		n = n / 10;
		t++;
	}
	return (t);
}

char	*ft_itoa(int n)
{
	char	*dest;
	size_t	i;
	long	l;

	l = n;
	dest = (char *)malloc(sizeof(char) * (ft_numberofchar(l) + 1));
	if (dest == NULL)
		return (0);
	i = ft_numberofchar(l);
	dest[i--] = '\0';
	if (l < 0)
	{
		dest[0] = '-';
		l = l * -1;
	}
	if (l == 0)
	{
		dest[0] = '0';
	}
	while (l > 0)
	{
		dest[i--] = l % 10 + 48;
		l = l / 10;
	}
	return (dest);
}
