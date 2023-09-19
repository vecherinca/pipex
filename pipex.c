/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria <maria@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:36:15 by mklimina          #+#    #+#             */
/*   Updated: 2023/08/23 00:03:02 by maria            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "pipex.h"
#include <sys/wait.h>


char *get_path(char *cmd, t_pipex pipex)
{
	char *path;
	char *intermediate; 
	int flag;
	int i;
	i = 0;
	while (pipex.paths[i] !=  NULL)
	{
		intermediate = ft_strjoin(pipex.paths[i], "/");
		path = ft_strjoin(intermediate, cmd);
		free(intermediate);
		if (access(path, R_OK) != -1)
		{
			flag = 1;
			return(path);
		}
		else
		{	
			free(path);
			flag = 0;
		}
		i++;
	}
	if (flag == 0)
	{
		printf("Command %s does not exist", cmd);
		exit(23);
	}
	return(0);
}

char **parse_env(char **env)
{
	int i;
	char *prefix = "PATH=";
	char *path;
	i = 0;
	while(env[i] != NULL)
	{
		if (ft_strncmp(env[i], prefix, ft_strlen(prefix)) == 0)
		{
			path = ft_strstr(env[i], "PATH=");
			return(ft_split(path, ':'));
		}
		i++;
			
	}
	return(0);
}

t_a_list	*create_list(int argc, char **argv, t_pipex pipex)
{
	t_a_list	*temp;
	t_a_list	*head;
	int			i;
	head = NULL;
	i = 2;
	while (i < argc - 1)
	{
		temp = malloc(sizeof(t_a_list));
		if (!temp)
			return (NULL);
		temp->cmd = ft_split(argv[i], ' ');	
		temp -> path = get_path(temp->cmd[0], pipex);
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
	return (point);
}

t_pipex init(char **argv, t_pipex pipex, int argc, char **env)
{
	pipex.paths = parse_env(env);
	pipex.file1 = open(argv[1], O_RDONLY);
	pipex.file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex.cmd_count = argc - 3; 
	pipex.cmd = define_list(argc, argv, pipex);
	return(pipex);
}


int	main(int argc, char **argv, char **env)
{
	int result;
	t_pipex pipex;
	pipex = init(argv, pipex, argc, env);
	execute(pipex, env);	
	free_list(pipex.cmd -> first, pipex.cmd);
	close(pipex.file1);
	close(pipex.file2);
	free_2dim(pipex.paths);
				
}
