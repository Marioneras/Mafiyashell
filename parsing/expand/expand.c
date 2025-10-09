/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:43:16 by safamran          #+#    #+#             */
/*   Updated: 2025/10/09 19:24:44 by safamran         ###   ########.fr       */
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
			str = new;
	if (new)
		return (new);
	return (str);
}

char	*after_racc(int *i, int original_i, t_obj *obj, char *str)
{
	if (str[*i] == '\0')
		return (*i = original_i + 1, ft_strdup("$"));
	if (str[*i] == '?' || check_char(str[*i]) == 0)
		return (*i = original_i + 2, ft_itoa(obj->exit_code));
	if (str[*i] == '\0' || check_char(str[*i]) == 0)
		return (*i = original_i + 1, ft_strdup("$"));
	if (ft_isdigit(str[*i]))
		return (*i = original_i + 2, ft_strdup(""));
	return (NULL);
}

char	*after_dollar(char *str, int *i, char **envp, t_obj *obj)
{
	char	*var_name;
	char	*replace;
	int		start;
	int		original_i;
	char	*result;

	original_i = *i;
	(*i)++;
	result = after_racc(i, original_i, obj, str);
	if (result != NULL)
		return (result);
	start = *i;
	while (str[*i] != '\0' && check_char(str[*i]) == 1)
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (ft_strdup("$"));
	replace = get_value(var_name, envp);
	if (replace == NULL)
		return (ft_strdup(""));
	result = ft_strdup(replace);
	return (free(replace), result);
}

char	*get_value(char *var_name, char **envp)
{
	char	*result;
	int		i;
	int		varlen;
	int		envlen;

	if (!envp || !var_name)
		return (free(var_name), NULL);
	varlen = ft_strlen(var_name);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(var_name, envp[i], varlen) == 0
			&& envp[i][varlen] == '=')
		{
			envlen = ft_strlen(envp[i]);
			result = ft_substr(envp[i], varlen + 1, envlen - varlen - 1);
			return (free(var_name), result);
		}
		i++;
	}
	return (free(var_name), NULL);
}
