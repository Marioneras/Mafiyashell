/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:11:02 by safamran          #+#    #+#             */
/*   Updated: 2025/10/08 16:15:09 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (0);
		}
		i++;
	}
	clone[i] = ft_strdup(obj->cmd->argv[a]);
	if (!clone[i])
	{
		ft_freetab(clone);
		return (0);
	}
	clone[i + 1] = NULL;
	return (1);
}

int	check_alpha(t_obj *obj)
{
	int	i;

	i = 0;
	while (obj->cmd->argv[i] != NULL)
	{
		if (ft_isalpha(obj->cmd->argv[i][0]) == 0)
			return (i);
		i++;
	}
	return (0);
}
