/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:29:10 by jrasser           #+#    #+#             */
/*   Updated: 2022/03/14 06:17:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 10
#include "get_next_line.h"

/*
 * 	0  = fin de fichier
 *	-1 = error
 */

static int is_end_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char *get_next_line(int fd)
{
	char 			*buffer;
	static char		**lines;
	char 			*line;
	static char		*buffer_tmp;
	char 			c;
	size_t 			i;
	static size_t 	j;
	int 			ret;
	int 			nb_de_concat;
	static int 		line_actuel;
	static char 	*temp;

	nb_de_concat = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);

	// recupere text jusquau buffersize
	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret == -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[ret] = '\0';




	// printf("--------- DEBUT ---------\n");
	// printf("buffer initial :\n'%s'\n\n", buffer);
	printf("ret : %d, buffer size : %d, buffer : \"%s\" \n", ret, BUFFER_SIZE, buffer);

	// buffer non plein
	if (ret < BUFFER_SIZE)	// check fin de fichier
	{
		if (ret)
			lines = ft_split(buffer, '\n');
		line = lines[j];

		i = 0;
		while (line[i] != '\n' && line[i])
			i++;
		line[i] = '\n';
		j++;
		//printf("line de split : %s", line);
		return (line);
	}
	// buffer plein
	else if (ret == BUFFER_SIZE)
	{
		// printf("is end line ? : %d ", (!(is_end_line(buffer))));
		while (!(is_end_line(buffer)))
		{
			if (nb_de_concat == 0)
				line = "";
			nb_de_concat++;
			
			printf("line avant : \"%s\" ", line);
			line = ft_strlcat(line, buffer);
			printf("line apres : \"%s\"\n", line);
			buffer[0] = '\0';

			ret = read(fd, buffer, BUFFER_SIZE);
			if (ret == -1)
			{
				free(buffer);
				return (NULL);
			}
			buffer[ret] = '\0';

			line = ft_strlcat(line, buffer);
			printf("line final : \"%s\"", line);

			// printf("fin de la ligne : \"%s\"\n\n\n", buffer);
		}
		printf("ligne actuel : %d, nb de concat : %d\n", line_actuel, nb_de_concat);
		

		line_actuel++;
		return (line);
	}
	else
		printf("hein ?!");

	return (NULL);
}

/*
	i = 0;
	while (lines[i] != NULL)
	{
		printf("là : %s", lines[i]);
		i++;
	}
	printf(" i : '%d'", i);
*/

/*
	// cherche le '\n' dans le buffer
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	printf("buffer[%ld] : '%c', ret : %d\n", i, buffer[i], ret);

	if (buffer[i] == '\0')
	{
		if (i == ret)
			printf("c'est pas fini\n");
		else
			printf("fin de fichier\n");
	}
	else if (buffer[i] == '\n')
	{
		printf("fin de ligne : buffer[%ld] : '%c'\n", i, buffer[i + 1]);

		// mise en mémoir du reste
		j = 0;
		while (buffer[i])
		{
			tmp[j] = buffer[i];
			j++;
			i++;
		}
		tmp[j] = '\0';
		i -= j;

		buffer[i + 1] = '\0';

		return (buffer);
	}
	else
		printf("jsais pas ou j'en suis là\n");

*/

// printf("\n\n\n'%s'    => ret : %d\n\n\n\n", str, ret);

// while ((c != '\n' || c == EOF) && i <= BUFFER_SIZE)
//{
//	buffer[i] = c;
//	read(fd, &c, 1);
//	i++;
// }
// buffer[i] = '\0';

// printf("'%c', \"%s\", nb_line : %ld, actuel ligne : %ld\n, len_line %d", c, buffer, nb_line, actual_line, length_line);

/*
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
*/

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

/*
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