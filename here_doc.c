/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:55:45 by mklimina          #+#    #+#             */
/*   Updated: 2023/10/03 17:17:03 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(t_pipex pipex)
{
	char	*check;

	while (1)
	{
		check = get_next_line(0);
		if (!check)
			return ;
		if (!ft_strcmp(check, pipex.limiter))
			break ;
		ft_putstr_fd(check, pipex.file1);
		free(check);
	}
	unlink("tmp.txt");
	free(check);
}
