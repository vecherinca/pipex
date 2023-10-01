/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:56:33 by mklimina          #+#    #+#             */
/*   Updated: 2022/12/15 16:02:11 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{	
	void	*output;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb * size < size)
		return (0);
	output = (void *)malloc(size * nmemb);
	if (!output)
		return (NULL);
	ft_bzero(output, nmemb * size);
	return (output);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*output;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	output = ft_calloc(sizeof(char), len);
	if (!output)
		return (NULL);
	while (s1[i] != '\0')
	{
		output[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		output[i] = s2[j];
		i++;
		j++;
	}
	return (output);
}

int	ft_do_ze_line(char **line, char *buffer, char **stash)
{
	*line = ft_strjoin("", *stash);
	if (!*line)
		return (1);
	free(*stash);
	*stash = ft_strjoin(*line, buffer);
	if (!*stash)
		return (free(*line), 1);
	free(*line);
	return (0);
}
