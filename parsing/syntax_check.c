/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:36:59 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 18:57:58 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_pipe(t_token *current)
{
	if (!current->previous || !current->next)
		return (false);
	if (current->previous->type == PIPE || current->next->type == PIPE)
		return (false);
	if (current->previous->type == TRUNC || current->previous->type == APPEND
		|| current->previous->type == INPUT
		|| current->previous->type == HEREDOC)
		return (false);
	return (true);
}

static bool	check_redirection(t_token *current)
{
	if (current->previous)
	{
		if (current->previous->type == TRUNC
			|| current->previous->type == APPEND
			|| current->previous->type == INPUT
			|| current->previous->type == HEREDOC)
			return (false);
	}
	return (true);
}

static int	check_pipe_syntax(t_token *token)
{
	if (token->type == PIPE && !check_pipe(token))
		return (display_error_message(PIPE_ERROR, NULL), PIPE_ERROR);
	if (is_pipe_char_in_wrong_context(token))
		return (display_error_message(PIPE_ERROR, NULL), PIPE_ERROR);
	return (EXIT_SUCCESS);
}

static int	check_redirection_syntax(t_token *token)
{
	if (is_redirection_type(token->type) && !check_redirection(token))
		return (display_error_message(INVALID_OPERATOR, token->name),
			INVALID_OPERATOR);
	if (is_invalid_redirection_symbol(token))
		return (redirection_error(token->name));
	if (!token->next && is_redirection_type(token->type))
		return (display_error_message(MISSING_FILENAME, "newline"),
			MISSING_FILENAME);
	return (EXIT_SUCCESS);
}

int	check_syntax(t_token *head)
{
	t_token	*current;
	int		status;

	if (!head)
		return (false);
	current = head;
	while (current)
	{
		status = check_pipe_syntax(current);
		if (status != EXIT_SUCCESS)
			return (status);
		status = check_redirection_syntax(current);
		if (status != EXIT_SUCCESS)
			return (status);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
