/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:29:10 by jrasser           #+#    #+#             */
/*   Updated: 2022/03/21 22:09:26 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_buffer_empty(char *buffer)
{
	int	i;

	if (buffer == NULL)
		return (1);
	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buffer[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

int	is_buffer_end_line(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] && buffer[i] == '\n')
		return (1);
	return (0);
}

int	ft_read(int fd, char *buffer)
{
	int	ret;

	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret == -1)
	{
		free(buffer);
		return (-1);
	}
	buffer[ret] = '\0';
	return (ret);
}

char	*ft_calloc(char *buffer)
{
	int	i;

	i = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;
	int			ret;

	line = malloc(sizeof(char));
	if (line == NULL)
		return (NULL);
	if (is_buffer_empty(buffer))
	{
		buffer = ft_calloc(buffer);
		ret = ft_read(fd, buffer);
	}
	line = ft_strlcat(line, buffer);
	if (ret < 1)
		return (NULL);
	while (!(is_buffer_end_line(buffer)) && ret > 0)
	{
		ret = ft_read(fd, buffer);
		line = ft_strlcat(line, buffer);
	}
	buffer = update_buffer(buffer);
	return (line);
}
