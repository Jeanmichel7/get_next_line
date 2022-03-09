/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:29:10 by jrasser           #+#    #+#             */
/*   Updated: 2022/03/09 03:29:12 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 4
#include <unistd.h>
#include "get_next_line.h"
#include <stdio.h>

static void ft_read_char(int fd, char *c, int *ret)
{
	*ret = read(fd, c, 1);
	if (*c != '\n')
		printf("'%c' %d \n", *c, *ret);
}

char *get_next_line(int fd)
{
	char *buffer;
	char c;
	size_t i;
	static size_t nb_line;
	static size_t final_line;
	size_t actual_line;
	int ret;

	actual_line = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);



	printf("\navant : nb line : %ld, final line : %ld, actuel %ld\n", nb_line, final_line, actual_line);

	// condition sorti fian line
	if (nb_line >= final_line && nb_line != 0 && final_line != 0)
	{
		nb_line++;
		printf("haaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
		printf("bufer de fin %s\n", buffer);
		return (buffer);
	}


	// charge 1° char
	ft_read_char(fd, &c, &ret);
	if (ret == 0 && c != '\n')
		return (NULL);
	buffer[0] = c;

	if (nb_line == 0) // premiere ligne
	{
		i = 1;
		while (c != '\n' && i < BUFFER_SIZE)
		{
			ft_read_char(fd, &c, &ret);
			if (ret == 0 && c != '\n')
				final_line = actual_line;
			buffer[i] = c;
			i++;
		}
		printf("1erline: nb line : %ld, final line : %ld, actuel %ld\n", nb_line, final_line, actual_line);
		nb_line++;
		buffer[i] = '\0';
		return (buffer);
	}
	else
	{
		// récupere la ligne
		while (actual_line < nb_line)
		{
			while (c != '\n' && ret != 0)
			{
				ft_read_char(fd, &c, &ret);
				if (ret == 0 && c != '\n')
					final_line = nb_line;
			}
			actual_line++;
		}
		printf("milieu: nb line : %ld, final line : %ld, actuel %ld\n", nb_line, final_line, actual_line);

		// charge 1° char
		ft_read_char(fd, &c, &ret);
		if (ret == 0 && c != '\n')
			final_line = nb_line;
		buffer[0] = c;

		// condition sorti fian line
		if (nb_line == final_line && nb_line != 0)
		{
			printf("fin ! bah alors ??\n");
			free(buffer);
			return (NULL);
		}

		i = 1;
		while (c != '\n' && i < BUFFER_SIZE && ret != 0)
		{
			ft_read_char(fd, &c, &ret);
			if (ret == 0 && c != '\n')
			{
				final_line = nb_line;
			}
			buffer[i] = c;
			i++;
		}

		printf("apres : nb line : %ld, final line : %ld, actuel %ld\n\n", nb_line, final_line, actual_line);
		buffer[i] = '\0';
		nb_line++;
		return (buffer);
	}

	return (NULL);

	/*
	i = 0;
	ft_read_char(fd, &c, &ret);
	if (ret == 0)
		final_line = nb_line + 1;
	buffer[i++] = c;




	while (ret != 0 && c != '\n' && i < BUFFER_SIZE)
	{
		ft_read_char(fd, &c, &ret);
		if (ret == 0)
			final_line = nb_line + 1;
		buffer[i] = c;
		i++;
	}

	printf("apres : nb line : %ld, final line : %ld, actuel %ld\n", nb_line, final_line, actual_line);

	buffer[i] = '\0';
	nb_line++;
	return (buffer);
	*/
}

/*
	while (actual_line <= nb_line)
	{
		read(fd, &c, 1);
		if (c == '\n')
			actual_line++;
		if (actual_line == nb_line)
		{
			i = 0;
			while ((c != '\n' || c == EOF) && i <= BUFFER_SIZE)
			{
				buffer[i] = c;
				read(fd, &c, 1);
				i++;
			}
			buffer[i] = '\0';
			return (buffer);
		}
		//printf("'%c', \"%s\", nb_line : %ld, actuel ligne : %ld\n, len_line %d", c, buffer, nb_line, actual_line, length_line);
	}
*/