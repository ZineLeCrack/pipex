/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:38:51 by rlebaill          #+#    #+#             */
/*   Updated: 2025/04/17 10:05:16 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	write_in_pipe(t_pipex *data)
{
	char	**cmd;
	char	*path;

	dup2(data->infile, STDIN_FILENO);
	dup2(data->pipe_fd[1], STDOUT_FILENO);
	close_all(data);
	cmd = ft_split(data->av[2], ' ');
	if (!cmd)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(1);
	}
	path = ft_find_path(data, cmd[0]);
	if (!path)
	{
		free_split(cmd);
		exit(1);
	}
	execve(path, cmd, data->env);
	ft_putstr_fd("command not found\n", 2);
	free_split(cmd);
	free(path);
	exit(1);
}

static void	write_in_file(t_pipex *data)
{
	char	**cmd;
	char	*path;

	dup2(data->pipe_fd[0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close_all(data);
	cmd = ft_split(data->av[3], ' ');
	if (!cmd)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(1);
	}
	path = ft_find_path(data, cmd[0]);
	if (!path)
	{
		free_split(cmd);
		exit(1);
	}
	execve(path, cmd, data->env);
	ft_putstr_fd("command not found\n", 2);
	free_split(cmd);
	free(path);
	exit(1);
}

static int	init_data(t_pipex *data, char **argv, char **envp)
{
	data->av = argv;
	data->env = envp;
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		return (ft_putstr_fd("failed to open infile\n", 2), 1);
	data->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1)
		return (ft_putstr_fd("failed to open outfile\n", 2),
			close(data->infile), 1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	pid_t	pid;

	if (argc != 5)
		return (ft_putstr_fd("usage: ./pipex infile cmd cmd outfile\n", 2), 1);
	if (init_data(&data, argv, envp))
		return (1);
	if (pipe(data.pipe_fd) == -1)
		return (ft_putstr_fd("pipe error\n", 2), 1);
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork error\n", 2), 1);
	if (pid == 0)
		write_in_pipe(&data);
	if (fork() == 0)
		write_in_file(&data);
	close_all(&data);
	wait(NULL);
	wait(NULL);
	return (0);
}
