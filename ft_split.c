/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:31:20 by mklimina          #+#    #+#             */
/*   Updated: 2023/07/30 19:33:13 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

/*
Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.
*/

void	free_tab(char **tab, int index)
{
	while (index >= 0)
	{
		free(tab[index]);
		index--;
	}
	free(tab);
}

int	numb_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while ((s[i] == c))
			i++;
		if ((s[i] != c) && s[i] != '\0')
			count++;
		while ((s[i] != c) && s[i])
			i++;
	}
	return (count);
}

void	create_tab(char **tab, char const *s, char c)
{
	size_t	index;
	size_t	len;

	index = 0;
	len = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		while (*s != c && *s != '\0')
		{
			++len;
			++s;
		}
		if (len > 0)
		{
			tab[index] = malloc(sizeof(char) * len + 1);
			if (!tab[index])
				return (free_tab(tab, index));
			tab[index][len] = '\0';
		}
		index++;
		len = 0;
	}
}

void	fill_tab(char **tab, char const *s, char c)
{
	size_t	j;
	size_t	index;

	index = 0;
	j = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			++s;
		while (*s != c && *s != '\0')
		{
			tab[index][j] = *s;
			j++;
			++s;
		}
		index++;
		j = 0;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	number_words;

	if (!s)
		return (0);
	number_words = numb_words(s, c);
	if (number_words == 0)
		return (ft_calloc(1, sizeof(char *)));
	tab = malloc(sizeof(char *) * (number_words + 1));
	if (!tab)
		return (NULL);
	tab[number_words] = NULL;
	create_tab(tab, s, c);
	fill_tab(tab, s, c);
	return (tab);
}
