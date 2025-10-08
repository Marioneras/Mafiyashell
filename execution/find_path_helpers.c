/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:14:32 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 15:44:46 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_variable(char **env, char *variable)
{
	int	i;
	int	variable_len;

	variable = ft_strjoin(variable, "=");
	if (!variable)
		return (NULL);
	variable_len = ft_strlen(variable);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], variable, variable_len) == 0)
			return (free(variable), &env[i][variable_len]);
		i++;
	}
	free(variable);
	return (NULL);
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}
