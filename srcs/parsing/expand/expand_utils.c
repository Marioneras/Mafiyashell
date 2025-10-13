/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:24:46 by safamran          #+#    #+#             */
/*   Updated: 2025/10/09 19:24:30 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_escape_dollar(char *str, t_handle *handle, char *result)
{
	char	*prefsuf;
	char	*dollar;
	char	*tmp;

	prefsuf = ft_substr(str, handle->start, handle->i - handle->start);
	if (prefsuf)
	{
		tmp = join_and_free(result, prefsuf);
		if (tmp)
			result = tmp;
		free(prefsuf);
	}
	dollar = ft_strdup("$");
	if (dollar)
	{
		tmp = join_and_free(result, dollar);
		if (tmp)
			result = tmp;
		free(dollar);
	}
	handle->i += 2;
	handle->start = handle->i;
	return (result);
}

char	*process_segment(char *str, t_handle *handle, char *result, t_obj *obj)
{
	char	*prefsuf;
	char	*var;

	prefsuf = ft_substr(str, handle->start, handle->i - handle->start);
	if (prefsuf)
	{
		result = join_and_free(result, prefsuf);
		free(prefsuf);
	}
	var = after_dollar(str, &handle->i, obj->env, obj);
	if (var)
	{
		result = join_and_free(result, var);
		free(var);
	}
	handle->start = handle->i;
	return (result);
}

static char	*process_loop(char *str, t_handle *handle, char *result, t_obj *obj)
{
	bool	in_single;
	bool	in_double;

	in_single = false;
	in_double = false;
	while (str[handle->i] != '\0')
	{
		tracking(str[handle->i], &in_single, &in_double);
		if (str[handle->i] == '\\' && str[handle->i + 1] == '$'
			&& str[handle->i + 1] != '\0')
			result = handle_escape_dollar(str, handle, result);
		else if (str[handle->i] == '$' && !in_single)
			result = process_segment(str, handle, result, obj);
		else
			(handle->i)++;
	}
	return (result);
}

char	*process_string(char *str, t_handle *handle, char *result, t_obj *obj)
{
	char	*prefsuf;

	result = process_loop(str, handle, result, obj);
	if (handle->start < handle->i)
	{
		prefsuf = ft_substr(str, handle->start, handle->i - handle->start);
		if (prefsuf)
		{
			result = join_and_free(result, prefsuf);
			free(prefsuf);
		}
	}
	return (result);
}

char	*expand_var(char *str, char **envp, t_obj *obj)
{
	char		*result;
	t_handle	handle;

	(void)envp;
	handle.i = 0;
	handle.start = 0;
	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	result = process_string(str, &handle, result, obj);
	return (result);
}
