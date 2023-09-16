#include "pipex.h"

void	free_2dim(char **to_free)
{
	int i;
	i = 0;
	while (to_free[i]!=NULL)
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

void	free_list(t_a_list *head, t_head_a *main)
{
	t_a_list	*current;
	t_a_list	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current -> path);
		free_2dim(current -> cmd);
		free(current);
		current = next;
	}
	free(main);
}