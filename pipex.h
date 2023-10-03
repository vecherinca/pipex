/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:36:37 by mklimina          #+#    #+#             */
/*   Updated: 2023/10/03 17:17:47 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "gnl/get_next_line.h"
# include "pipex.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct t_a_list
{
	char			*path;
	char			**cmd;
	struct t_a_list	*next;
}					t_a_list;

typedef struct t_head_a
{
	t_a_list		*first;
}					t_head_a;

typedef struct t_pipex
{
	int				fd[2];
	int				file1;
	int				file2;
	char			*limiter;
	int				cmd_count;
	char			**paths;
	char			**cmds;
	char			**args;
	char			*cmd1;
	char			*cmd2;
	int				is_here_doc;
	t_head_a		*cmd;

}					t_pipex;

void				print(t_pipex pipex);
char				**ft_split(char const *s, char c);
void				*ft_calloc(size_t nmemb, size_t size);
t_head_a			*define_list(int argc, char **argv, t_pipex pipex);
char				**parse_env(char **env);
char				*ft_strstr(char *str, char *to_find);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strlen(const char *s);
void				ft_lstadd_back(t_a_list **lst, t_a_list *new);
char				*ft_strjoin(char const *s1, char const *s2);
void				print_cmd_does_not_exist(char *cmd);
void				free_2dim(char **to_free);
void				execute(t_pipex pipex, char **env);
void				free_list(t_a_list *head, t_head_a *main);
void				init_child(int count, t_pipex pipex, char **env,
						t_a_list *cmd);
int					ft_strcmp(char *s1, char *s2);
t_pipex				init(char **argv, t_pipex pipex, int argc, char **env);
t_pipex				here_doc_init(int argc, char **argv, char **env,
						t_pipex pipex);

void				here_doc(t_pipex pipex);
void				ft_putstr_fd(char *s, int fd);
char				*return_path(char *path, char *cmd);
#endif