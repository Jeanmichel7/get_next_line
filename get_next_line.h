/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:29:12 by jrasser           #+#    #+#             */
/*   Updated: 2022/03/21 18:46:31 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
char	*ft_strlcat(char *dst, char *src);
size_t  ft_strlen(const char *str);

#endif


/* BUFFER_SIZE */

#ifndef BUFFER_SIZE

# define BUFFER_SIZE 10

#endif