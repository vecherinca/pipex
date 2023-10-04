/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:55:17 by mklimina          #+#    #+#             */
/*   Updated: 2023/10/04 23:31:43 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_argc(int argc)
{
	if (argc < 5)
	{
		ft_putstr_fd("Verify your commands once again.", 2);
		exit(26);
	}
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*output;
	int		len;

	len = ft_strlen(src);
	i = 0;
	output = malloc(sizeof(char) * len + 1);
	if (!output)
		return (0);
	while (src[i])
	{
		output[i] = src[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

void	free_everything(t_pipex *pipex)
{
	free_list(pipex->cmd->first, pipex->cmd);
	free_2dim(pipex->paths);
	free(pipex->pid);
}

void	execute_commands(t_pipex pipex, t_a_list *cmd, char **env, int i)
{
	while (cmd != NULL)
	{
		pipe(pipex.fd);
		pipex.pid[i] = fork();
		if (pipex.pid[i] < 0)
		{
			free_everything(&pipex);
			exit(1);
		}
		else if (pipex.pid[i] == 0)
			setup_child(i, &pipex, env, cmd);
		else
		{
			close(pipex.fd[1]);
			if (i > 0)
				close(pipex.prev);
			pipex.prev = pipex.fd[0];
		}
		cmd = cmd->next;
		i++;
	}
	close(pipex.fd[0]);
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
