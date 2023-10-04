/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:58:27 by mklimina          #+#    #+#             */
/*   Updated: 2023/10/04 23:23:01 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_first_file(t_pipex *pipex)
{
	if (pipex->is_here_doc == 0)
	{
		pipex->file1 = open(pipex->infile, O_RDONLY);
		if (pipex->file1 < 0)
		{
			free_everything(pipex);
			exit(24);
		}
	}
	return (pipex->file1);
}

int	open_last_file(t_pipex *pipex)
{
	pipex->file2 = open(pipex->outfile, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (pipex->file2 < 0)
	{
		free_everything(pipex);
		exit(24);
	}
	return (pipex->file2);
}

void	do_exec(t_pipex *pipex, char **env, t_a_list *cmd)
{
	if (cmd->path)
		execve(cmd->path, cmd->cmd, env);
	else
	{
		free_everything(pipex);
		exit(1);
	}
}

void	setup_child(int count, t_pipex *pipex, char **env, t_a_list *cmd)
{
	if (count == 0)
	{
		pipex->file1 = open_first_file(pipex);
		dup2(pipex->file1, STDIN_FILENO);
		close(pipex->file1);
	}
	if (count == pipex->cmd_count - 1)
	{
		pipex->file2 = open_last_file(pipex);
		dup2(pipex->file2, STDOUT_FILENO);
		close(pipex->file2);
	}
	if (count != 0)
	{
		dup2(pipex->prev, STDIN_FILENO);
		close(pipex->prev);
	}
	if (count != pipex->cmd_count - 1)
		dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	do_exec(pipex, env, cmd);
}

void	execute(t_pipex pipex, char **env)
{
	int			i;
	t_a_list	*cmd;

	i = 0;
	cmd = pipex.cmd->first;
	pipex.prev = -1;
	pipex.pid = malloc(sizeof(int) * pipex.cmd_count);
	if (!pipex.pid)
	{
		free_everything(&pipex);
		exit(25);
	}
	execute_commands(pipex, cmd, env, i);
	i = 0;
	while (i < pipex.cmd_count)
	{
		waitpid(pipex.pid[i], NULL, 0);
		i++;
	}
	free(pipex.pid);
}
