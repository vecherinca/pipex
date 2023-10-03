#include "pipex.h"

void here_doc(t_pipex pipex)
{
	char *check;

	while (1)
	{
		check = get_next_line(0);
		if(!check)
			return ;
		if (!ft_strcmp(check, pipex.limiter))
			break;
		ft_putstr_fd(check, pipex.file1); 
		free(check);
	}
	unlink("tmp.txt");
	free(check);
}