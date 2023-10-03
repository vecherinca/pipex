#include "pipex.h"

t_pipex	init(char **argv, t_pipex pipex, int argc, char **env)
{
	pipex.paths = parse_env(env);
	pipex.file1 = open(argv[1], O_RDONLY);
	pipex.file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex.cmd_count = argc - 3;
	pipex.is_here_doc = 0;
	pipex.cmd = define_list(argc, argv, pipex);
	return (pipex);
}

t_pipex	here_doc_init(int argc, char **argv, char **env, t_pipex pipex)
{
	pipex.paths = parse_env(env);
	pipex.limiter = ft_strjoin(argv[2], "\n");
	pipex.file1 = open("tmp.txt", O_CREAT | O_RDWR, 0666);
	pipex.file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex.is_here_doc = 1;
	pipex.cmd_count = 2;
	pipex.cmd = define_list(argc, argv, pipex);
	return(pipex);
}