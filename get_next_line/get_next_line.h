/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:50:09 by mklimina          #+#    #+#             */
/*   Updated: 2022/12/14 18:32:46 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>

char	*get_next_line(int fd);
int		ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
void	ft_bzero(void *s, size_t n);
int		ft_do_ze_line(char **line, char *buffer, char **stash);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
#endif