/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:54:34 by mklimina          #+#    #+#             */
/*   Updated: 2023/10/04 16:50:26 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	init(char **argv, t_pipex pipex, int argc, char **env)
{
	pipex.paths = parse_env(env);
	pipex.infile = argv[1];
	pipex.outfile = argv[argc - 1];
	pipex.cmd_count = argc - 3;
	pipex.is_here_doc = 0;
	pipex.cmd = define_list(argc, argv, pipex);
	if (!pipex.cmd)
	{
		free_everything(&pipex);
		exit(25);
	}
	return (pipex);
}

t_pipex	here_doc_init(int argc, char **argv, char **env, t_pipex pipex)
{
	pipex.paths = parse_env(env);
	pipex.limiter = ft_strjoin(argv[2], "\n");
	pipex.file1 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (pipex.file1 < 0)
	{
		free_everything(&pipex);
		exit(24);
	}
	pipex.outfile = argv[argc - 1];
	pipex.is_here_doc = 1;
	pipex.cmd_count = 2;
	pipex.cmd = define_list(argc, argv, pipex);
	if (!pipex.cmd)
	{
		free_everything(&pipex);
		exit(25);
	}
	return (pipex);
}
