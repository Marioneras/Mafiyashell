#include "minishell.h"


int	ft_tabcount(char **tab)
{
	int i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	env_match(char *line, char *var_name)
{
	int i = 0;
	if (!line || !var_name)
		return (0);

	while (var_name[i] && line[i] && line[i] != '=')
	{
		if (line[i] != var_name[i])
			return (0);
		i++;
	}
	return (var_name[i] == '\0' && (line[i] == '=' || line[i] == '\0'));
}

void	unset_it(t_obj *obj, int i, int len)
{
	free(obj->env[i]);
	if (i < len - 1)
	{
		obj->env[i] = obj->env[len - 1];
		obj->env[len - 1] = NULL;
	}
	else
	{
		obj->env[i] = NULL;
	}
}

void	search_line(char *str, t_obj *obj)
{
	int i = 0;
	int len;

	if (!str || !obj || !obj->env)
		return ;

	len = ft_tabcount(obj->env);
	while (obj->env[i])
	{
		if (env_match(obj->env[i], str))
		{
			unset_it(obj, i, len);
			break ;
		}
		i++;
	}
}

int	run_unset(t_obj *obj)
{
	int i;

	i = 1;
	if (!obj || !obj->cmd || !obj->cmd->argv[1])
		return (EXIT_FAILURE);
	if (check_option(obj->cmd->argv) == 0)
	{
		ft_putstr_fd("unset: No options\n", 2);
		return (EXIT_FAILURE);
	}
	while (obj->cmd->argv[i])
	{
		search_line(obj->cmd->argv[i], obj);
		i++;
	}
	return (EXIT_SUCCESS);
}
