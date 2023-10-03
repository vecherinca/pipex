/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:58:27 by mklimina          #+#    #+#             */
/*   Updated: 2023/10/03 17:14:34 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_child(int count, t_pipex pipex, char **env, t_a_list *cmd)
{
	if (count == 0)
	{
		dup2(pipex.file1, STDIN_FILENO);
		dup2(pipex.fd[1], STDOUT_FILENO);
		close(pipex.file1);
		close(pipex.fd[0]);
	}
	if (count == pipex.cmd_count - 1)
	{
		dup2(pipex.file2, STDOUT_FILENO);
		close(pipex.file2);
		close(pipex.file1);
	}
	else
	{
		dup2(pipex.fd[1], STDOUT_FILENO);
		close(pipex.file2);
		close(pipex.fd[0]);
	}
	execve(cmd->path, cmd->cmd, env);
	perror("execve");
	close(pipex.fd[1]);
	exit(1);
}

void	init_child(int count, t_pipex pipex, char **env, t_a_list *cmd)
{
	pid_t	pid;

	if (pipe(pipex.fd) == -1)
	{
		ft_putstr_fd("An error occurred with the pipe creation", 2);
		exit(1);
		// Don't forget to free resources
	}
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("An error occurred with the forking", 2);
		exit(1);
	}
	if (pid == 0)
	{
		setup_child(count, pipex, env, cmd);
	}
	else
	{
		waitpid(pid, 0, 0);
		close(pipex.fd[1]);
		dup2(pipex.fd[0], STDIN_FILENO);
	}
}

void	execute(t_pipex pipex, char **env)
{
	int			i;
	t_a_list	*cmd;

	i = 0;
	cmd = pipex.cmd->first;
	while (cmd != NULL)
	{
		init_child(i, pipex, env, cmd);
		cmd = cmd->next;
		i++;
	}
}
