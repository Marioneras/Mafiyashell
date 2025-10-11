/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:11:37 by safamran          #+#    #+#             */
/*   Updated: 2025/10/08 16:49:30 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_cd(t_obj *obj)
{
	DIR		*dir;
	char	*path;

	if (check_cd(obj->cmd->argv) == 1)
		return (1);
	path = obj->cmd->argv[1];
	dir = opendir(path);
	if (dir == NULL)
	{
		ft_putstr_fd("mafiyashell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	closedir(dir);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("mafiyashell: cd: Unable to change directory\n", 2);
		return (1);
	}
	if (update_env(obj) != 0)
		return (ft_putstr_fd("mafiyashell: cd: error\n", 2), 1);
	return (0);
}

char	*get_cd_value(const char *key, char **env)
{
	size_t	key_len;
	int		i;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (ft_strdup(env[i] + key_len + 1));
		i++;
	}
	return (NULL);
}

int	update_env(t_obj *obj)
{
	char	**oldpwd;
	char	**pwd;
	char	**saved_argv;

	saved_argv = obj->cmd->argv;
	oldpwd = get_oldpwd(obj->env);
	if (!oldpwd)
		return (1);
	obj->cmd->argv = oldpwd;
	run_export(obj);
	obj->cmd->argv = saved_argv;
	ft_freetab(oldpwd);
	pwd = get_pwd();
	if (!pwd)
		return (1);
	obj->cmd->argv = pwd;
	run_export(obj);
	obj->cmd->argv = saved_argv;
	ft_freetab(pwd);
	return (0);
}

int	check_cd(char **argv)
{
	if (!argv[1])
	{
		ft_putstr_fd("mafiyashell: cd: no absolute or relative path\n", 2);
		return (1);
	}
	if (argv[2])
	{
		ft_putstr_fd("mafiyashell: cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}
