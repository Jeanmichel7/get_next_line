/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:29:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/03/26 19:57:26 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strlcat(char *line, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	//printf("----------strlcat-DEBUT --------\nline : '%s'\nbuffer: '%s'\n", line, buffer);

	new_str = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buffer)) + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (line && line[i])
	{
		new_str[i] = line[i];
		i++;
	}
	if (line)
		free(line);
	j = 0;
	while (buffer && buffer[j] && buffer[j] != '\n')
		new_str[i++] = buffer[j++];
	if (buffer[j] == '\n')
		new_str[i++] = buffer[j++];
	new_str[i] = '\0';
	//printf("buffer : '%s'\n", buffer);
	//printf("new line : '%s'\n--------strlcat -END -------\n\n", new_str);
	return (new_str);
}

char	*update_buffer(char *buffer)
{
	long		i;
	long		j;
	char	*tmp;

	i = 0;
	while (buffer[i] != '\n' && i < BUFFER_SIZE)
		i++;
	tmp = malloc(sizeof(char) * (BUFFER_SIZE - i + 1));
	if (tmp == NULL)
		return (NULL);
	i++;
	j = 0;
	while (i < BUFFER_SIZE && buffer[i])
		tmp[j++] = buffer[i++];
	tmp[j] = '\0';
	free(buffer);
	if (tmp[0] == '\0')
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

int	is_buffer_empty(char *buffer)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(buffer);
	if (buffer == NULL || len == 0)
		return (1);
	i = 0;
	while (i < len)
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
	if (buffer[i] == '\n')
		return (1);
	return (0);
}

/*
int	check_ret(int ret, char *line, char *buffer)
{
	if (ret == 0 && !(line))
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

	if (buffer && buffer[0] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	line = NULL;
	ret = 1;
	if (is_buffer_empty(buffer))
		buffer = ft_calloc(buffer, BUFFER_SIZE);
	if (is_buffer_empty(buffer))
		ft_read(fd, buffer);
	line = ft_strlcat(line, buffer);
	while (!(is_buffer_end_line(buffer)) && ret > 0)
	{
		ret = ft_read(fd, buffer);
		line = ft_strlcat(line, buffer);
	}
	if (check_ret(ret, line, buffer))
		return (NULL);
	if (ret > 0)
		buffer = update_buffer(buffer);
	return (line);
}
*/
