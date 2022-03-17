/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:29:10 by jrasser           #+#    #+#             */
/*   Updated: 2022/03/17 04:29:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 100
#include "get_next_line.h"

/*
 * 	0  = fin de fichier
 *	-1 = error
 */


static int is_end_line(char *str)
{
	int i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			ret++;
		i++;
	}
	return (ret);
}

char *get_next_line(int fd)
{
	char 			*buffer;
	static char		**lines;
	char 			*line;
	char 			*line_tmp;
	static char		*buffer_tmp;
	char 			c;
	size_t 			i;
	static size_t 	j;
	size_t			i_bfr;
	int				ret;
	int 			nb_de_concat;
	static int 		line_actuel;
	static char 	*temp;

	nb_de_concat = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);

	if (line_actuel == 0)
	{
		buffer_tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer_tmp == NULL)
			return (NULL);
		buffer_tmp[BUFFER_SIZE] = '\0';
	}

	


	/*************************************************************/
	/*******                Verfi buffer_tmp            **********/
	/*************************************************************/


	printf("b_tmp dbu: '%-10s'		", buffer_tmp);
	if (is_end_line(buffer_tmp))
	{
		// met de coté le après \n dans buffer_tmp
		//retour (****\n)

		line_tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (line_tmp == NULL)
			return (NULL);
		line_tmp[BUFFER_SIZE] = '\0';

		// recopie le buffer_tmp dans line_tmp
		i = 0;
		while (buffer_tmp[i] && i < BUFFER_SIZE)
		{
			line_tmp[i] = buffer_tmp[i];
			buffer_tmp[i] = '\0';
			i++;
		}
		line_tmp[i] = '\0';
		//printf("'%s' = '%s'		", line_tmp, buffer_tmp);
		
		i = 0;
		while (line_tmp[i] != '\n' && line_tmp[i])
			i++;
		i++;
		i_bfr = 0;
		while (line_tmp[i] && i_bfr < BUFFER_SIZE - i)
		{
			buffer_tmp[i_bfr] = line_tmp[i];
			//printf("bfr_tmp[%ld] = line_tmp[%ld] = %c = %c, %p %p\n", i_bfr, i, buffer_tmp[i_bfr], line_tmp[i], buffer_tmp, line_tmp);
			line_tmp[i] = '\0';
			i++;
			i_bfr++;
		}

		buffer_tmp[i_bfr] = '\0';
		printf("tmp '%-10s'	", buffer_tmp);
		//printf("line_tmp : '%s' ", line_tmp);


		line_actuel++;
		return (line_tmp);

	}
	//printf("line : '%s' ", line);

	else if (buffer_tmp)
	{
		line = "blaaaaaaaaaaaaa";
		line = ft_strlcat(line, buffer_tmp);
	}


	// recupere text jusquau buffersize
	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret == -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[ret] = '\0';


	// buffer non plein
	if (ret < BUFFER_SIZE && ret)	// check fin de fichier
	{
		//printf("buffer non plein	");
		if (ret)
			lines = ft_split(buffer, '\n');
		line = lines[j];

		i = 0;
		while (line[i] != '\n' && line[i])
			i++;
		
		line[i] = '\n';
		//i++;
		//while (line[i])
		//{
		//	line[i] = '\0';
		//	i++;
		//}
		j++;
		//printf("line de split : %s", line);
		line_actuel++;
		return (line);
	}


	// buffer plein
	else if (ret == BUFFER_SIZE)
	{
		while (!(is_end_line(buffer)))
		{
			if (nb_de_concat == 0)
			{
				//line = "";
				line = ft_strlcat(line, buffer);
			}
			nb_de_concat++;
			
			//printf("line avant : \"%s\" ", line);
			//line = ft_strlcat(line, buffer);
			//printf("line apres : \"%s\"\n", line);

			ret = read(fd, buffer, BUFFER_SIZE);
			if (ret == -1)
			{
				free(buffer);
				return (NULL);
			}
			buffer[ret] = '\0';

			if (nb_de_concat)
				line = ft_strlcat(line, buffer);
			//printf("line final : \"%s\"", line);

			// printf("fin de la ligne : \"%s\"\n\n\n", buffer);
		}
		//printf("ligne actuel : %d, nb de concat : %d\n", line_actuel, nb_de_concat);
		


		// buffer avec retour ligne
		i = 0;
		while (line[i] != '\n' && line[i])
			i++;
		i++;
		i_bfr = 0;
		while (line[i] && i_bfr < BUFFER_SIZE - i)
		{
			buffer_tmp[i_bfr] = line[i];
			//printf("bfr_tmp[%d] = line[%d] = %c = %c\n", i_bfr, i, buffer_tmp[i_bfr], line[i]);
			line[i] = '\0';
			i++;
			i_bfr++;
		}

		buffer_tmp[i_bfr] = '\0';
		//printf("tmp en fin '%s'\n", buffer_tmp);




		line_actuel++;
		return (line);
	}

	// ret = 0
	else
	{
		line = lines[j];

		i = 0;
		while (line[i] != '\n' && line[i])
			i++;
		
		line[i] = '\n';
		//i++;
		//while (line[i])
		//{
		//	line[i] = '\0';
		//	i++;
		//}
		j++;
		//printf("line de split : %s", line);
		line_actuel++;
		return (line);
	}




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