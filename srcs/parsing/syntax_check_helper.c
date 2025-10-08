/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:56:44 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 18:59:11 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection_type(int type)
{
	return (type == TRUNC || type == APPEND || type == INPUT
		|| type == HEREDOC);
}

bool	is_pipe_char_in_wrong_context(t_token *token)
{
	return (token->name[0] == '|' && token->type != PIPE);
}

bool	is_invalid_redirection_symbol(t_token *token)
{
	return ((token->name[0] == '<' && token->type != INPUT
			&& token->type != HEREDOC) || (token->name[0] == '>'
			&& token->type != TRUNC && token->type != APPEND));
}
