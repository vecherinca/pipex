/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 23:32:35 by mklimina          #+#    #+#             */
/*   Updated: 2023/10/04 23:38:08 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*iter_paths(char *cmd, t_pipex pipex)
{
	int		flag;
	int		i;
	char	*path;

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

char	*get_path2(char *cmd)
{
	int	flag;

	if (access(cmd, F_OK | X_OK) != -1)
	{
		flag = 1;
		return (cmd);
	}
	else
	{
		flag = 0;
		free(cmd);
	}
	if (flag == 0)
		print_cmd_does_not_exist(cmd);
	return (0);
}
