/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:29:31 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/18 11:52:32 by mrezki           ###   ########.fr       */
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

int	execute_cmd(char **cmd, char *env[], t_shell *sh)
{
	char	*path;
	char	*path_env;
	int		pid;

	path_env = search_env(sh->env, "PATH");
	if (!path_env)
		return (print_error(cmd[0], MSG_NOFILE), ERR_NOFILE);
	path = find_path(cmd[0], env, sh, path_env);
	if (!path)
		return (free(path), print_error(cmd[0], MSG_NOCMD), ERR_NOCMD);
	if (access(path, X_OK) != 0)
		return (free(path), print_error(cmd[0], MSG_NOPERM), ERR_NOPERM);
	pid = fork();
	if (!pid)
	{
		execve(path, cmd, env);
		free(path);
		exit(print_error(cmd[0], "execve"));
	}
	else
		if (waitpid(pid, &sh->exit_status, 0) < 0)
			return (free(path), print_error("waitpid", NULL));
	return (free(path), WEXITSTATUS(sh->exit_status));
}
