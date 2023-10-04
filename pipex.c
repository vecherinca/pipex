/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:36:15 by mklimina          #+#    #+#             */
/*   Updated: 2023/10/04 17:38:25 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char	*get_path(char *cmd, t_pipex pipex)
{
	char	*path;
	int		flag;
	int		i;

	i = 0;
	while (pipex.paths[i] != NULL)
	{
		path = return_path(pipex.paths[i], cmd);
		if (access(path, R_OK) != -1)
		{
			flag = 1;
			return (path);
		}
		else
		{
			free(path);
			flag = 0;
		}
		i++;
	}
	if (flag == 0)
		print_cmd_does_not_exist(cmd);
	return (0);
}

char	**parse_env(char **env)
{
	int		i;
	char	*prefix;
	char	*path;

	prefix = "PATH=";
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], prefix, ft_strlen(prefix)) == 0)
		{
			path = ft_strstr(env[i], "PATH=");
			return (ft_split(path, ':'));
		}
		i++;
	}
	return (0);
}

t_a_list	*create_list(int argc, char **argv, t_pipex pipex)
{
	t_a_list	*temp;
	t_a_list	*head;
	int			i;

	head = NULL;
	i = 2 + pipex.is_here_doc;
	while (i < argc - 1)
	{
		temp = malloc(sizeof(t_a_list));
		if (!temp)
			return (NULL);
		temp->cmd = ft_split(argv[i], ' ');
		temp->path = get_path(temp->cmd[0], pipex);
		temp->next = NULL;
		ft_lstadd_back(&head, temp);
		i++;
	}
	return (head);
}

t_head_a	*define_list(int argc, char **argv, t_pipex pipex)
{
	t_head_a	*point;

	point = malloc(sizeof(t_head_a));
	if (!point)
		return (NULL);
	point->first = create_list(argc, argv, pipex);
	if (!point->first)
	{
		free_everything(&pipex);
		exit(25);
	}
	return (point);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		ft_putstr_fd("Verify your commands once again.", 2);
		exit(26);
	}
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		if (argc != 6)
		{
			ft_putstr_fd("Verify your commands once again.", 2);
			exit(26);
		}
		pipex = here_doc_init(argc, argv, env, pipex);
		here_doc(pipex);
		free(pipex.limiter);
	}
	else
	{
		pipex = init(argv, pipex, argc, env);
	}
	execute(pipex, env);
	free_list(pipex.cmd->first, pipex.cmd);
	free_2dim(pipex.paths);
}
