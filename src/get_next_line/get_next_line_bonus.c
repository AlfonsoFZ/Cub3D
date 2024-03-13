/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:05:01 by Alfofern          #+#    #+#             */
/*   Updated: 2023/02/08 10:06:11 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_get_next(char *mybuffer)
{
	int		i;
	int		j;
	char	*next_line;

	i = 0;
	while (mybuffer[i] && mybuffer[i] != '\n')
		i++;
	if (!mybuffer[i])
	{
		free(mybuffer);
		return (NULL);
	}
	next_line = ft_calloc((ft_strlen(mybuffer) - i + 1), sizeof(char));
	if (!next_line)
		return (NULL);
	i++;
	j = 0;
	while (mybuffer[i])
		next_line[j++] = mybuffer[i++];
	free(mybuffer);
	return (next_line);
}

static char	*ft_return_line(char *mybuffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!mybuffer[i])
		return (NULL);
	while (mybuffer[i] && mybuffer[i] != '\n')
		i++;
	if (ft_strchr(mybuffer, '\n'))
		line = ft_calloc(i + 2, sizeof(char));
	else
		line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (mybuffer[i] && mybuffer[i] != '\n')
	{
		line[i] = mybuffer[i];
		i++;
	}
	if (mybuffer[i] && mybuffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*ft_read_fd(int fd, char *mybuffer)
{
	char	*buff;
	int		nbreaded;

	if (mybuffer && ft_strchr(mybuffer, '\n'))
		return (mybuffer);
	buff = malloc(BUFFER_SIZE + 1);
	nbreaded = 1;
	while (nbreaded > 0)
	{
		nbreaded = read(fd, buff, BUFFER_SIZE);
		if (nbreaded == -1)
		{
			free(buff);
			free(mybuffer);
			return (NULL);
		}
		buff[nbreaded] = 0;
		if (nbreaded > 0)
			mybuffer = ft_strjoin(mybuffer, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (mybuffer);
}

char	*get_next_line(int fd)
{
	static char	*mybuffer[10240];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	mybuffer[fd] = ft_read_fd(fd, mybuffer[fd]);
	if (!mybuffer[fd])
		return (NULL);
	line = ft_return_line(mybuffer[fd]);
	mybuffer[fd] = ft_get_next(mybuffer[fd]);
	return (line);
}
