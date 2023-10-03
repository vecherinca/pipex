/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:58:27 by mklimina          #+#    #+#             */
/*   Updated: 2023/10/03 21:42:23 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"






// ./pipex Makefile ls cat grep wc lsblk outfile


// 0 = ls
// last = lsblk

// 0 != cat grep wc lsblk

// last != ls cat grep wc 

void	setup_child(int count, t_pipex *pipex, char **env, t_a_list *cmd)
{
	// free(pid);
	// open files here !!!!!
	// if it fails exit
	if (count == 0)
	{
		if (pipex -> is_here_doc == 0)
			pipex->file1 = open(pipex -> infile, O_RDONLY);
		dup2(pipex->file1, STDIN_FILENO);
		close(pipex->file1);
	}
	if (count == pipex->cmd_count - 1)
	{
		pipex->file2 = open(pipex -> outfile, O_CREAT | O_RDWR | O_TRUNC, 0666);
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
	if (cmd->path)
		execve(cmd->path, cmd->cmd, env);
	write(2, "Cmd error\n", 10);
	// free EVERYTHING
	exit(1);
}

void	execute(t_pipex pipex, char **env)
{
	int			i;
	t_a_list	*cmd;

	i = 0;
	cmd = pipex.cmd->first;
	pipex.prev = -1;
	int *pid = malloc(sizeof(int) * pipex.cmd_count);
	while (cmd != NULL)
	{
		pipe(pipex.fd);
		pid[i] = fork();
		if (pid[i] < 0)
		{
			// free thingd
			exit(1);
		}
		else if (pid[i] == 0)
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
	i = 0;
	while (i < pipex.cmd_count)
	{
		waitpid(pid[i], NULL, 0);
    	i++;
	}
	// here do a while loop for every pid of every forks, its cleaner and better
	// so factorize ur code, a lot of things are in common in each of ur childs so u can simply malloc a table of int for your forks
}
