/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:29:55 by raisufaj          #+#    #+#             */
/*   Updated: 2025/05/01 20:51:36 by raisufaj         ###   ########.fr       */
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
	char	*created_dir;
	char	*cmd_path;
	int		i;

	i = 0;
	while (path[i])
	{
		created_dir = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(created_dir, argument);
		free(created_dir);
		if (access(cmd_path, 0) == 0)
			return (cmd_path);
		free(cmd_path);
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
