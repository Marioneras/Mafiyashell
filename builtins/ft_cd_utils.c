/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:27:57 by safamran          #+#    #+#             */
/*   Updated: 2025/10/08 16:53:43 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (free(result), NULL);
	pwd_value = get_cd_value("PWD", env);
	if (!pwd_value)
	{
		pwd_value = ft_strdup(getcwd(buffer, PATH_MAX));
		if (!pwd_value)
			return (free(result[0]), free(result), NULL);
	}
	result[1] = ft_strjoin("OLDPWD=", pwd_value);
	free(pwd_value);
	if (!result[1])
		return (free(result[0]), free(result), NULL);
	result[2] = NULL;
	return (result);
}
