/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:29:55 by raisufaj          #+#    #+#             */
/*   Updated: 2025/04/29 16:58:18 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	ft_open(char **av, int file_nb)
{
	int	fd_open;

	if (file_nb == 0)
		fd_open = open(av[1], O_RDONLY);
	if (file_nb == 1)
		fd_open = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_open < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	return (fd_open);
}

char	*ft_get_command(char **path, char *argument)
{
	char	*to_free;
	char	*to_return;
	int		i;

	i = 0;
	while (path[i])
	{
		to_free = ft_strjoin(path[i], "/");
		to_return = ft_strjoin(to_free, argument);
		free(to_free);
		if (access(to_return, 0) == 0)
			return (to_return);
		free(to_return);
		i++;
	}
	return (NULL);
}

char	**ft_get_path(char **envp)
{
	int		i;
	char	**path_split;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", LEN_PATH) == 0)
			path_split = ft_split(envp[i] + LEN_PATH, ':');
		i++;
	}
	if (path_split == NULL)
		return (NULL);
	return (path_split);
}

void	ft_close(t_pipex *data, int fd_nb)
{
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	if (fd_nb == 0)
		close(data->fd_infile);
	else if (fd_nb == 1)
		close(data->fd_outfile);
	else
		return ;
}

void	ft_execve(t_pipex *data, char **envp)
{
	data->path = ft_get_path(envp);
	data->command = ft_get_command(data->path, data->argument[0]);
	if (data->command == NULL)
	{
		ft_free(data, 1);
		perror("Error");
		exit(EXIT_FAILURE);
	}
	ft_free(data, 1);
	execve(data->command, data->argument, envp);
}
