/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:52:24 by jrasser           #+#    #+#             */
/*   Updated: 2023/09/01 19:56:50 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*str;

	fd1 = open("man_read.txt", O_RDONLY);
	if (fd1 == -1)
	{
		printf("imposible d'ouvrir le fichier\n");
		return (1);
	}
	printf("fd1 : %d, ", fd1);

	fd2 = open("man_read2.txt", O_RDONLY);
	if (fd2 == -1)
	{
		printf("imposible d'ouvrir le fichier 2\n");
		return (1);
	}
	printf("fd2 : %d, ", fd2);

	fd3 = open("man_read3.txt", O_RDONLY);
	if (fd3 == -1)
	{
		printf("imposible d'ouvrir le fichier 3\n");
		return (1);
	}
	printf("fd3 : %d\n", fd3);

	while ((str = get_next_line(fd3)))
	{
		printf("fd3: %s", str);
		free(str);
	}

	str = get_next_line(fd1);
	printf("fd1: %s", str);
	free(str);
	str = get_next_line(fd2);
	printf("fd2: %s", str);
	free(str);

	printf("\n");
	if (close(fd1))
	{
		printf("imposible de fermer le fichier 1\n");
		return (1);
	}
	if (close(fd2))
	{
		printf("imposible de fermer le fichier 2\n");
		return (1);
	}
	if (close(fd3))
	{
		printf("imposible de fermer le fichier 3\n");
		return (1);
	}
	return (0);
}
