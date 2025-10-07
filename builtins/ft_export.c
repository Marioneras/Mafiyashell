#include "minishell.h"

int	is_var_exist(char *var, char **env)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = 0;
	while(var[var_len] && var[var_len] != '=')
		var_len++;
	while(env[i])
	{
		if (ft_strncmp(var, env[i], var_len) == 0 && env[i][var_len] == '=')
			return i;
		i++;
	}
	return (-1);
}

int	new_tab(t_obj *obj, int a)
{
	char **new;
	int len;
	len = ft_tabcount(obj->env) + 2;
	new = malloc(sizeof(char *) * len);
	if (!new)
		return 0;
	if (!clone(obj, new, a))
	{
		free(new);
		return 0;
	}
	char **old_env = obj->env;
	obj->env = new;
	ft_freetab(old_env);
	return (1);
}

int	check_alpha(t_obj *obj)
{
	int i;
	
	i = 0;
	while(obj->cmd->argv[i] != NULL)
	{
		if(ft_isalpha(obj->cmd->argv[i][0]) == 0)
			return (i);
		i++;
	}
	return (0);
}
/*
void	expand_export(t_obj *obj)
{
	int	i;
	char	*result;
	i = 1;
	while(obj->cmd->argv[i] != NULL)
	{
		//ft_putstr_fd(obj->cmd->argv[i], 2);
		//ft_putstr_fd("\n", 2);
		if (is_export_expand(obj->cmd->argv[i]) == 1)
			result = expand_var(obj->cmd->argv[i], obj->env, obj);
		if (result && result != obj->cmd->argv[i])
		{
			free(obj->cmd->argv[i]);
			obj->cmd->argv[i] = ft_strdup(result);
			free(result);
		}
		i++;
	}	
}

int	is_export_expand(char *str)
{
	if (nb_dollar(str) == 0)
		return (0);
	int i;
	while(str[i] != '=' && str[i])
		i++;
	if (str[i] != '\0')
		return (0);
	if (nb_quote(str + i + 1) != 0)
	{
		if (quote_check(str + i + 1) == 0)
		{
			//printf("\n%s\n\n", str);
			//printf("\nhere\n");
			return (0);
		}
	}
	return (1);
}*/

int	run_export(t_obj *obj)
{
	int		i;
	char	**clone_av;
	int		var_index;
	
	if (!obj->cmd->argv[1])
	{
		ft_putstr_fd("mafiyashell: export: No argument\n", 2);
		return (EXIT_FAILURE);
	}
	int a =	check_alpha(obj);
	if (a != 0)
	{
		obj->exit_code = 1;
		ft_putstr_fd("mafiyashell: export: `", 2);
		ft_putstr_fd(obj->cmd->argv[a], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	i = 1;
	//expand_export(obj);
	clone_av = clone_env(obj->cmd->argv);
	while (clone_av[i] != NULL)
	{
		var_index = is_var_exist(clone_av[i], obj->env);
		if (var_index >= 0)
		{
			free(obj->env[var_index]);
			obj->env[var_index] = ft_strdup(clone_av[1]);
			if(!obj->env[var_index])
			{
				ft_freetab(clone_av);
				return (EXIT_FAILURE);
			}
		}
		else
		{
			if (!new_tab(obj, i))
			{
					ft_freetab(clone_av);
					return (EXIT_FAILURE);
			}
		}
	i++;
	}
	ft_freetab(clone_av);
	return (EXIT_SUCCESS);
}

int	clone(t_obj *obj, char **clone, int a)
{
	int	i;

	i = 0;
	while (obj->env[i] != NULL)
	{
		clone[i] = ft_strdup(obj->env[i]);
		if (!clone[i])
		{
			ft_freetab(clone);
			return 0;
		}
		i++;
	}
	clone[i] = ft_strdup(obj->cmd->argv[a]);
	if (!clone[i])
	{
			ft_freetab(clone);
			return 0;
	}
	clone[i + 1] = NULL;
	return 1;
}

void	ft_freetab(char **tab)
{
    int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
