#include "pipex.h"

char *return_path(char *path, char *cmd)
{
	char	*intermediate;
	char	*merged_path;
	intermediate = ft_strjoin(path, "/");
	merged_path = ft_strjoin(intermediate, cmd);
	free(intermediate);
	return (merged_path);
}
void print_cmd_does_not_exist(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(":Command does not exist", 2);
}