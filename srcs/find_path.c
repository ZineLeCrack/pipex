/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:19:53 by rlebaill          #+#    #+#             */
/*   Updated: 2025/04/17 10:07:03 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_dubble_strjoin(char *s1, char *s2, char *s3)
{
	char	*rep;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	rep = ft_strjoin(tmp, s3);
	free(tmp);
	return (rep);
}

static char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(ft_strchr(env[i], '=') + 1, ':');
			if (!paths)
			{
				ft_putstr_fd("malloc failed\n", 2);
				return (NULL);
			}
			return (paths);
		}
		i++;
	}
	ft_putstr_fd("command not found\n", 2);
	return (NULL);
}

char	*ft_find_path(t_pipex *data, char *cmd)
{
	char	**paths;
	char	*path;
	int		len;
	int		i;

	if (!cmd)
		return (ft_putstr_fd("command not found\n", 2), NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return (ft_strdup(cmd));
	len = ft_strlen(cmd);
	i = 0;
	paths = get_paths(data->env);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		path = ft_dubble_strjoin(paths[i], "/", cmd);
		if (access(path, X_OK) == 0)
			return (free_split(paths), path);
		free(path);
		i++;
	}
	ft_putstr_fd("command not found\n", 2);
	free_split(paths);
	return (NULL);
}
