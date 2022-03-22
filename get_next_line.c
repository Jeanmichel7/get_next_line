/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:29:10 by jrasser           #+#    #+#             */
/*   Updated: 2022/03/22 18:58:53 by jrasser          ###   ########.fr       */
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

	line = NULL;
	ret = 1;
	//printf("buffer : %s		", buffer);
	if (is_buffer_empty(buffer))
	{
		buffer = ft_calloc(buffer);
		ret = ft_read(fd, buffer);
	}
	if (ret < 1)
		return (NULL);
	line = ft_strlcat(line, buffer);
	//printf("ret : %d	", ret);
	while (!(is_buffer_end_line(buffer)) && ret > 0)
	{
		ret = ft_read(fd, buffer);
		line = ft_strlcat(line, buffer);
		//printf("buffer : '%s'		line '%s'	", buffer, line);
	}
	buffer = update_buffer(buffer);
	return (line);
}
