/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:33:06 by raisufaj          #+#    #+#             */
/*   Updated: 2025/04/29 17:01:08 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# ifndef LEN_PATH
#  define LEN_PATH 5

# endif

# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int		pipe_fd[2];
	int		fd_infile;
	int		fd_outfile;
	pid_t	pid_child1;
	pid_t	pid_child2;
	char	**argument;
	char	**path;
	char	*command;
}	t_pipex;

void	ft_putstr_fd(char *s, int fd);

char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int c);
char	**ft_split(char const *s, char c);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);

void	ft_close(t_pipex *data, int fd_nb);
void	ft_execve(t_pipex *data, char **envp);
char	*ft_get_command(char **path, char *argument);
char	**ft_get_path(char **envp);
int		ft_open(char **av, int file_nb);

#endif