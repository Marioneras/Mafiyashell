/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:36:59 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/20 19:52:59 by mberthou         ###   ########.fr       */
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

int	check_syntax(t_token *head)
{
	t_token	*current;

	if (!head)
		return (false);
	current = head;
	while (current)
	{
		if (current->type == PIPE && !check_pipe(current))
			return (display_error_message(PIPE_ERROR, NULL), PIPE_ERROR);
		if (current->name[0] == '|' && current->type != PIPE)
			return (display_error_message(PIPE_ERROR, NULL), PIPE_ERROR);
		if ((current->type == TRUNC || current->type == APPEND
			|| current->type == INPUT || current->type == HEREDOC)
			&& !check_redirection(current))
			return (display_error_message(INVALID_OPERATOR, current->name), INVALID_OPERATOR);
		if ((current->name[0] == '<' && (current->type != INPUT
			&& current->type != HEREDOC)) || (current->name[0] == '>'
			&& (current->type != TRUNC && current->type != APPEND)))
			return (redirection_error(current->name));
		if (!current->next && (current->type == TRUNC || current->type == APPEND
			|| current->type == INPUT || current->type == HEREDOC))
			return (display_error_message(MISSING_FILENAME, "newline"), MISSING_FILENAME);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
