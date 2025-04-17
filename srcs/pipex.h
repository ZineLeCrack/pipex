/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:43:06 by rlebaill          #+#    #+#             */
/*   Updated: 2025/04/17 09:58:47 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	**env;
	char	**av;
	int		infile;
	int		outfile;
	int		pipe_fd[2];
}	t_pipex;

void	close_all(t_pipex *data);
void	free_split(char **cmd);
char	*ft_find_path(t_pipex *data, char *cmd);

#endif