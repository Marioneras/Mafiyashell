/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:30:06 by safamran          #+#    #+#             */
/*   Updated: 2025/10/09 17:35:06 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_exist(char *var, char **env)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = 0;
	while (var[var_len] && var[var_len] != '=')
		var_len++;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], var_len) == 0 && env[i][var_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	new_tab(t_obj *obj, int a)
{
	char	**new;
	int		len;
	char	**old_env;

	len = ft_tabcount(obj->env) + 2;
	new = malloc(sizeof(char *) * len);
	if (!new)
		return (0);
	if (!clone(obj, new, a))
	{
		free(new);
		return (0);
	}
	old_env = obj->env;
	obj->env = new;
	ft_freetab(old_env);
	return (1);
}

int	handle_var(t_obj *obj, char *var, char **clone_av, int i)
{
	int	var_index;

	var_index = is_var_exist(var, obj->env);
	if (var_index >= 0)
	{
		free(obj->env[var_index]);
		obj->env[var_index] = ft_strdup(var);
		if (!obj->env[var_index])
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
	return (EXIT_SUCCESS);
}

int	process_export_vars(t_obj *obj, char **clone_av)
{
	int	i;

	i = 1;
	while (clone_av[i] != NULL)
	{
		if (handle_var(obj, clone_av[i], clone_av, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	ft_freetab(clone_av);
	return (EXIT_SUCCESS);
}

int	run_export(t_obj *obj)
{
	int		a;
	char	**clone_av;

	if (!obj->cmd->argv[1])
	{
		ft_putstr_fd("mafiyashell: export: No argument\n", 2);
		return (EXIT_FAILURE);
	}
	a = check_alpha(obj);
	if (a != 0)
	{
		obj->exit_code = 1;
		ft_putstr_fd("mafiyashell: export: `", 2);
		ft_putstr_fd(obj->cmd->argv[a], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	clone_av = clone_env(obj->cmd->argv);
	if (!clone_av)
		return (EXIT_FAILURE);
	return (process_export_vars(obj, clone_av));
}
