/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:29:31 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/26 23:14:22 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*join_path(char *path, char *cmd)
{
	char	*tmp;
	char	*new_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (perror("Malloc"), NULL);
	new_path = ft_strjoin(tmp, cmd);
	if (!new_path)
		return (perror("Malloc"), NULL);
	free(tmp);
	return (new_path);
}

char	*find_path(char *cmd, char *env[], t_shell *sh, char *path_env)
{
	char	**paths;
	char	*path;
	int		i;

	if (cmd[0] == '/')
		return (cmd);
	paths = ft_split(path_env, ":");
	if (!paths)
		return (perror("Malloc"), NULL);
	i = 0;
	while (paths[i])
	{
		path = join_path(paths[i], cmd);
		if (!path)
			return (NULL);
		if (!access(path, F_OK))
			return (free_split(paths), path);
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}
