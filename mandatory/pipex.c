/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:30:26 by raisufaj          #+#    #+#             */
/*   Updated: 2025/04/29 17:16:48 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_init_fork(t_pipex *data, int child_nb)
{
	if (child_nb == 1)
	{
		data->pid_child1 = fork();
		if (data->pid_child1 < 0)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else if (child_nb == 2)
	{
		data->pid_child2 = fork();
		if (data->pid_child2 < 0)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_free(t_pipex *data, int check_nb)
{
	int	i;

	i = 0;
	if (check_nb == 0)
	{
		while (data->argument[i])
		{
			free(data->argument[i]);
			i++;
		}
		free(data->argument);
	}
	if (check_nb == 1)
	{
		i = 0;
		while (data->path[i])
		{
			free(data->path[i]);
			i++;
		}
		free(data->path);
	}
}

void	ft_first_child(char **av, char **envp, t_pipex *data)
{
	data->fd_infile = ft_open(av, 0);
	dup2(data->fd_infile, 0);
	dup2(data->pipe_fd[1], 1);
	ft_close(data, 0);
	data->argument = ft_split(av[2], ' ');
	if (!data->argument[0])
	{
		ft_free(data, 0);
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_second_child(char **av, char **envp, t_pipex *data)
{
	data->fd_outfile = ft_open(av, 1);
	dup2(data->fd_outfile, 1);
	dup2(data->pipe_fd[0], 0);
	ft_close(data, 1);
	data->argument = ft_split(av[3], ' ');
	if (!data->argument[0])
	{
		ft_free(data, 0);
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strchr(av[3], '/'))
		execve(data->argument[0], data->argument, envp);
	else
		ft_execve(data, envp);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	data;

	if (ac != 5)
		return (ft_putstr_fd("Error\nInvalid number of arguments\n", 2), 1);
	if (pipe(data.pipe_fd) < 0)
		return (perror("Error"), 1);
	ft_init_fork(&data, 1);
	if (data.pid_child1 == 0)
		ft_first_child(av, envp, &data);
	ft_init_fork(&data, 2);
	if (data.pid_child2 == 0)
		ft_second_child(av, envp, &data);
	ft_close(&data, 2);
	waitpid(data.pid_child1, NULL, 0);
	waitpid(data.pid_child1, NULL, 0);
	return (0);
}
