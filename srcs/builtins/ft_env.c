/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:17:30 by safamran          #+#    #+#             */
/*   Updated: 2025/10/08 15:17:32 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_env(t_obj *obj)
{
	int	i;

	i = 0;
	if (check_option(obj->cmd->argv) == 0)
	{
		printf("env: No options\n");
		return (EXIT_FAILURE);
	}
	while (obj->env[i] != NULL)
	{
		ft_putstr_fd(obj->env[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (EXIT_SUCCESS);
}
