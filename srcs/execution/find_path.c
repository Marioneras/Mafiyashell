/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:31:06 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 15:36:48 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_absolute_or_relative(char *cmd_name)
{
	return (cmd_name[0] == '/' || ft_strncmp(cmd_name, "./", 2) == 0);
}

static char	*join_path(const char *dir, const char *cmd)
{
	char	*prefix;
	char	*full_path;

	prefix = ft_strjoin(dir, "/");
	if (!prefix)
		return (NULL);
	full_path = ft_strjoin(prefix, cmd);
	ft_clear(&prefix);
	return (full_path);
}

static char	*find_executable_in_paths(char *cmd_name, char **paths)
{
	int		i;
	char	*exec;

	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		exec = join_path(paths[i], cmd_name);
		if (!exec)
			return (NULL);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		ft_clear(&exec);
	}
	return (NULL);
}

static char	*handle_direct_command(char *cmd_name)
{
	if (is_directory(cmd_name))
		return (display_error_message(21, cmd_name), NULL);
	return (ft_strdup(cmd_name));
}

char	*get_absolute_path(t_cmd *cmd, char **env)
{
	char	**paths;
	char	*exec;

	if (!cmd->argv[0] || !cmd->argv[0][0])
		return (NULL);
	if (is_absolute_or_relative(cmd->argv[0]))
		return (handle_direct_command(cmd->argv[0]));
	paths = ft_split(get_env_variable(env, "PATH"), ':');
	if (!paths)
	{
		display_error_message(NO_COMMAND, cmd->argv[0]);
		return (NULL);
	}
	exec = find_executable_in_paths(cmd->argv[0], paths);
	ft_clear_tab(paths);
	if (!exec)
	{
		display_error_message(NO_COMMAND, cmd->argv[0]);
		return (NULL);
	}
	return (exec);
}
