/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:29:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/03/21 17:27:00 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t  ft_strlen(const char *str)
{
    size_t  i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

static unsigned int	ft_count(const char *s, char c)
{
	unsigned int	count;
	unsigned int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
			i++;
		if (s[i])
			count++;
		else
			if (s[i - 1] != c)
				count++;
	}
	return (count);
}

char	*ft_sub_split(char const *s, char c, unsigned int *j)
{
	char			*str;
	unsigned int	k;

	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	k = 0;
	while (s[*j] == c && s[*j])
		(*j)++;
	while (s[*j] != c && s[*j])
		str[k++] = s[(*j)++];
	str[k] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_count(s, c))
	{
		tab[i++] = ft_sub_split(s, c, &j);
	}	
	tab[i] = NULL;
	return (tab);
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
