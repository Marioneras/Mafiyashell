/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:43:16 by safamran          #+#    #+#             */
/*   Updated: 2025/06/09 17:34:51 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_it(char *str, char **envp, t_obj *obj)
{
	char	*new;

	new = NULL;
	if (is_expand(str))
		new = expand_var(str, envp, obj);
	if (new != NULL)
	{
		//free(str); // Libère str si new est non-NULL
		str = new;
	}
	return (new ? new : str);
}

char	*after_dollar(char *str, int *i, char **envp, t_obj *obj)
{
	char	*var_name;
	char	*replace;
	int		start;
	int		original_i;

	original_i = *i;
	(*i)++;
	if (str[*i] == '\0')
	{
		*i = original_i + 1;
		return (ft_strdup("$"));
	}
	if (str[*i] == '?' || check_char(str[*i]) == 0)
	{
		*i = original_i + 2;
		return (ft_itoa(obj->exit_code));
	}
	if (str[*i] == '\0' || check_char(str[*i]) == 0 )
	{
		*i = original_i + 1;
		return (ft_strdup("$"));
	}

	if (ft_isdigit(str[*i]))
	{
		*i = original_i + 2;
		return (ft_strdup(""));
	}
	
	start = *i;
	while (str[*i] != '\0' && check_char(str[*i]) == 1)
		(*i)++;
	
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (ft_strdup("$"));

	replace = get_value(var_name, envp);
	if (replace == NULL)
		return (ft_strdup(""));
	char *result;
	result = ft_strdup(replace);
	free(replace);
	return (result);
}

char	*get_value(char *var_name, char **envp)
{
	char *result;
	int	i;
	int	varlen;
	int envlen;

	if (!envp || !var_name) // Vérifier envp et var_name
    {
        free(var_name);
        return (NULL);
    }

	varlen = ft_strlen(var_name);
	i = 0;
	while(envp[i] != NULL)
	{
		if (ft_strncmp(var_name, envp[i], varlen) == 0 && envp[i][varlen] == '=')
		{
			envlen = ft_strlen(envp[i]);
			result = ft_substr(envp[i], varlen + 1, envlen - varlen - 1);
			free(var_name);
			return (result);
		}
		i++;
	}
	free(var_name);
	return (NULL);
}
