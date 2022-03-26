/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:52:24 by jrasser           #+#    #+#             */
/*   Updated: 2022/03/27 00:19:43 by jrasser          ###   ########.fr       */
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

	fd = open("man_read.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("imposible d'ouvrir le fichier\n");
		return (1);
	}
	printf("fd : %d\n", fd);
	while ((str = get_next_line(fd)))
	{
		printf("%s", str);
		free(str);
	}
	printf("\n");
	if (close(fd))
	{
		printf("imposible de fermer le fichier\n");
		return (1);
	}
	return (0);
}
