/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirections_helper.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:42:11 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 18:49:19 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_end_of_pipeline(t_token *current)
{
	if (!current || !current->next)
		return (false);
	if (current->next->type == PIPE)
		return (true);
	if (current->next->next && current->next->type == LIMITER
		&& current->next->next->type == PIPE)
		return (true);
	if (!current->next->next)
		return (true);
	return (false);
}

bool	is_redirection_token(t_token *token)
{
	if (!token)
		return (false);
	return (token->type == INPUT || token->type == APPEND
		|| token->type == TRUNC || token->type == HEREDOC);
}

t_token	*find_first_redirection(t_token *token)
{
	while (token && !is_redirection_token(token))
		token = token->next;
	return (token);
}

bool	is_ignored_redirection(t_token *token, t_cmd *cmd)
{
	return (is_end_of_pipeline(token) || is_last_infile_or_outfile(cmd, token));
}

bool	is_valid_redirection(t_token *token)
{
	return (is_redirection_token(token)
		&& token->next && token->next->type != PIPE);
}
