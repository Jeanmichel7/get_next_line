/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:29:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/03/21 22:05:17 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t  ft_strlen(const char *str)
{
    size_t  i;

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
    char    *new_str;

	//printf("avant : '%s'	", line);
    new_str = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buffer) + 1));
    if (new_str == NULL)
		return (NULL);

	i = 0;
	while (line && line[i])
	{
		new_str[i] = line[i];
		i++;
	}
	j = 0;
	while (buffer[j] && buffer[j] != '\n')
	{	
		new_str[i] = buffer[j];
		//buffer[j] = '\0';
		i++;
		j++;
	}
	if (buffer[j] == '\n')
		new_str[i++] = '\n';
	new_str[i] = '\0';
	//printf("après : '%s'	", new_str);
	return (new_str);
}

char	*update_buffer(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (i == BUFFER_SIZE)
		free(buffer);
	else 
		buffer = buffer + i + 1;
	return (buffer);
}