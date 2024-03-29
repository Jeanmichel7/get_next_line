/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:52:24 by jrasser           #+#    #+#             */
/*   Updated: 2023/09/01 20:13:20 by jrasser          ###   ########.fr       */
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
	int		fd;
	char	*str;

	fd = open("man_read2.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("imposible d'ouvrir le fichier 2\n");
		return (1);
	}
	printf("fd : %d, ", fd);

	while ((str = get_next_line(fd)))
	{
		printf("fd: %s", str);
		free(str);
	}

	printf("\n");
	if (close(fd))
	{
		printf("imposible de fermer le fichier man_read2.txt\n");
		return (1);
	}
	return (0);
}
