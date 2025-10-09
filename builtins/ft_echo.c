/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:38:25 by mberthou          #+#    #+#             */
/*   Updated: 2025/09/12 19:00:43 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (false);
	i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static bool	check_arguments(char **args)
{
	if (!args || !*args)
		return (true);
	if (is_flag(*args))
		return (false);
	return (true);
}

int	ft_echo(t_obj *obj)
{
	bool	new_line;
	int		i;
	char	**args;

	args = &obj->cmd->argv[1];
	new_line = check_arguments(args);
	while ((args && *args) && is_flag(*args))
		args++;
	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
