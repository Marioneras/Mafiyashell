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
		ft_putstr_fd("mafiyashell: cd: No such file or directory\n", 2);
		return (1);
	}
	closedir(dir);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("mafiyashell: cd: Unable to change directory\n", 2);
		return (1);
	}
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
