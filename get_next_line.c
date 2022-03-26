/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:29:10 by jrasser           #+#    #+#             */
/*   Updated: 2022/03/26 19:58:09 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_calloc(char *buffer, long size)
{
	int	i;

	i = 0;
	buffer = malloc(sizeof(char) * (size + 1));
	if (buffer == NULL)
		return (NULL);
	while (i < size + 1)
		buffer[i++] = '\0';
	return (buffer);
}


int	check_ret(int ret, char *line, char *buffer)
{
	if (ret == 0 && buffer && buffer[0] == '\0')
	{
		free(buffer);
		return (0);
	}
	else if ((ret == 0 && !(line)) || ret == -1)
		return (1);
	return (0);
}


char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			ret;
	int			repet = 0;

	if (buffer && buffer[0] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	line = malloc(sizeof(char));
	line[0] = '\0';
	ret = 1;
	if (is_buffer_empty(buffer))
	{
		buffer = ft_calloc(buffer, BUFFER_SIZE);
		ret = ft_read(fd, buffer);
		if (ret == -1)
			return (NULL);
		else if (ret == 0)
		{
			free(buffer);
			return (NULL);
		}
	}
	line = ft_strlcat(line, buffer);
	
	while (!(is_buffer_end_line(buffer)) && ret > 0)
	{
		if (ft_strlen(buffer) != BUFFER_SIZE)
			buffer = ft_calloc(buffer, BUFFER_SIZE);
		ret = ft_read(fd, buffer);
		if (ret == -1)
			return (NULL);
		else if (ret == 0)
		{
			if (line)
				return (line);
			free(buffer);
			return (NULL);
		}
		line = ft_strlcat(line, buffer);
		repet++;
	}
	if (ret == 0 && !(is_buffer_empty(line)))
	{
		if (buffer[0] != '\0')
			buffer = update_buffer(buffer);
		if (buffer[0] == 0)
			free(buffer);
		return (line);
	}
	else if (ret == 0)
	{
		free (line);
		if (buffer && buffer[0] == 0)
			free(buffer);
		return (NULL);
	}
	//printf("buffer : '%s'\n", buffer);
	if (buffer[0] != '\0')
		buffer = update_buffer(buffer);
	if (buffer && buffer[0] == 0)
		free(buffer);
	return (line);
}
