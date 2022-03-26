/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:29:12 by jrasser           #+#    #+#             */
/*   Updated: 2022/03/26 23:47:12 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_strconcat(char *dst, char *src);
size_t  ft_strlen(const char *str);
char	*update_buffer(char *buffer);
int     ft_is_buffer_end_line(char *buffer);
int     ft_check_buffer_empty(char **buffer, int fd);
char	*ft_calloc(char *buffer, long size);
int	    ft_read(int fd, char *buffer);

#endif

/* BUFFER_SIZE */
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif