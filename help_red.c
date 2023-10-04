/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:55:17 by mklimina          #+#    #+#             */
/*   Updated: 2023/10/04 17:38:15 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_everything(t_pipex *pipex)
{
	free_list(pipex->cmd->first, pipex->cmd);
	free_2dim(pipex->paths);
	free(pipex->pid);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
