/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:11:37 by safamran          #+#    #+#             */
/*   Updated: 2025/10/08 05:13:45 by mberthou         ###   ########.fr       */
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
	{
		ft_putstr_fd("mafiyashell: cd: error\n", 2);
		return (1);
	}
	return (0);
}


char	**get_pwd(void)
{
	char	**result;
	char	buffer[PATH_MAX];

	result = malloc(sizeof(char *) * 3);
	if (!result)
		return (NULL);
	result[0] = ft_strdup("export");
	if (!result[0])
	{
		free(result);
		return (NULL);
	}
	result[1] = ft_strjoin("PWD=", getcwd(buffer, PATH_MAX));
	if (!result[1])
	{
		free(result[0]);
		free(result);
		return (NULL);
	}
	result[2] = NULL;
	return (result);
}

char *get_cd_value(const char *key, char **env)
{
	int	i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (ft_strdup(env[i] + key_len + 1));
	return (NULL);
}

char	**get_oldpwd(char **env)
{
	char	**result;
	char	*pwd_value;
	char	buffer[PATH_MAX];

	result = malloc(sizeof(char *) * 3);
	if (!result)
		return (NULL);
	result[0] = ft_strdup("export");
	if (!result[0])
	{
		free(result);
		return (NULL);
	}
	pwd_value = get_cd_value("PWD", env);
	if (!pwd_value)
	{
		pwd_value = ft_strdup(getcwd(buffer, PATH_MAX));
		if (!pwd_value)
		{
			free(result[0]);
			free(result);
			return (NULL);
		}
	}
	result[1] = ft_strjoin("OLDPWD=", pwd_value);
	free(pwd_value);
	if (!result[1])
	{
		free(result[0]);
		free(result);
		return (NULL);
	}
	result[2] = NULL;
	return (result);
}

int update_env(t_obj *obj)
{
	char	**oldpwd;
	char	**pwd;
	char	**saved_argv = obj->cmd->argv;

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
