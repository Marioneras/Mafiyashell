/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:57:35 by mberthou          #+#    #+#             */
/*   Updated: 2025/09/08 11:37:09 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_only_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while(str[i] != '\0')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return(1);
}

static void	racine_ex(t_token *head, char **envp)
{
	t_token	*current;
	char	*result;

	current = head;
	while (current)
	{
		result = expand_it(current->name, envp);
		if (result && result != current->name)
		{
			free(current->name);
			current->name = ft_strdup(result);
			free(result);
		}
		current = current->next;
	}
}

bool	parsing(t_obj *obj)
{
	int	syntax_error;

	if (is_only_space(obj->input) == 1)
		return (false);
	else if (check_quotes(obj->input) == 1)
	{
		obj->token = tokenize(obj->input);
		syntax_error = check_syntax(obj->token);
		if (syntax_error == PIPE_ERROR || syntax_error == MISSING_FILENAME
			|| syntax_error == INVALID_OPERATOR)
		{
			obj->exit_code = 2;
			return (free_token(obj->token), false);
		}
		else
		{
			racine_ex(obj->token, obj->env);
			quote_removal(obj->token);
			obj->cmd = create_cmd(obj);
			free_token(obj->token);
		}
	}
	else if (check_quotes(obj->input) == 0)
	{
		quote_error(obj->input);
		return (false);
	}
	return (true);
}
