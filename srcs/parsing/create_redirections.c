/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:40:27 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 21:55:32 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirections	*get_redirection(t_token *current)
{
	t_redirections	*new_red;

	new_red = (t_redirections *)ft_calloc(sizeof(t_redirections), 1);
	if (!new_red)
		return (NULL);
	if (current->type == INPUT)
		new_red->type = INPUT;
	else if (current->type == APPEND)
		new_red->type = APPEND;
	else if (current->type == TRUNC)
		new_red->type = TRUNC;
	else if (current->type == HEREDOC)
		new_red->type = HEREDOC;
	if (new_red->type != HEREDOC)
		new_red->name = ft_strdup(current->next->name);
	else
	{
		new_red->name = name_heredoc_file();
		new_red->limiter = ft_strdup(current->next->name);
		if (!new_red->limiter)
			return (free_redirections(new_red), NULL);
	}
	if (!new_red->name)
		return (free_redirections(new_red), NULL);
	return (new_red);
}

bool	is_last_infile_or_outfile(t_cmd *cmd, t_token *token)
{
	if (!token->next)
		return (true);
	if (token->type != HEREDOC && ft_strncmp(cmd->infile, token->next->name,
			ft_strlen(cmd->infile) + 1) == 0)
		return (true);
	else if (token->type == HEREDOC && ft_strncmp(cmd->limiter,
			token->next->name, ft_strlen(cmd->limiter) + 1) == 0)
		return (true);
	if (ft_strncmp(cmd->outfile, token->next->name, ft_strlen(cmd->outfile)
			+ 1) == 0)
		return (true);
	return (false);
}

static bool	append_redirection_safe(
	t_redirections **head, t_redirections *new_red)
{
	if (!new_red)
		return (false);
	append_redirections(*head, new_red);
	return (true);
}

t_redirections	*handle_redirections(t_token *token, t_cmd *cmd)
{
	t_token			*current;
	t_redirections	*head;
	t_redirections	*new_red;

	current = find_first_redirection(token);
	if (!current || is_ignored_redirection(current, cmd))
		return (NULL);
	head = get_redirection(current);
	if (!head)
		return (NULL);
	current = current->next;
	while (current && current->type != PIPE)
	{
		if (is_valid_redirection(current)
			&& !is_last_infile_or_outfile(cmd, current))
		{
			new_red = get_redirection(current);
			if (!append_redirection_safe(&head, new_red))
				return (free_redirections(head), NULL);
		}
		current = current->next;
	}
	return (head);
}
