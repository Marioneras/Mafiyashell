#include "minishell.h"

int	run_cd(t_obj *obj)
{
	DIR *dir;
	char *path;

	if (check_cd(obj->cmd->argv) == 1)
		return (1);
	path = obj->cmd->argv[1];
	dir = opendir(path);
	if (dir == NULL)
	{
		ft_putstr_fd("mafiyashell: cd: No such file or directory\n", 2);
		return (1);
	}
	closedir(dir);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("mafiyashell: cd: Unable to change directory\n", 2);
		return (1);
	}
	replace_pwd(obj, path);
	return (0);
}

void	replace_pwd(t_obj *obj, char *str)
{
	int	old;
	int	new;
	(void)*str;

	old = is_var_exist("OLDPWD=", obj->env);
	new = is_var_exist("PWD=", obj->env);	
	ft_putstr_fd(ft_itoa(new), 2);
	if (old != -1 && new != -1)
	{
		free(obj->env[old]);
		obj->env[old] = ft_strdup(obj->env[new]);
		if (!obj->env[old])
		{
			perror("");
			return ;
		}
	}
	if (new != -1)
	{
		free(obj->env[new]);
		obj->env[new] = getcwd(NULL, 0);
		if (!obj->env[new])
		{
			perror("");
			return ;
		}
	}	
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
