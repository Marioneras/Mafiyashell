/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:50:19 by mberthou          #+#    #+#             */
/*   Updated: 2025/09/04 19:31:19 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_arguments(t_token *node)
{
	t_token	*current;
	int		count;

	current = node;
	count = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == CMD || current->type == ARGUMENT
			|| current->type == EMPTY)
			count++;
		current = current->next;
	}
	return (count);
}

static void	set_value(char **destination, char *new_value)
{
	if (*destination)
		ft_clear(destination);
	(*destination) = new_value;
}

static void	init_cmd(t_cmd *new_cmd, t_token *token)
{
	int	count;

	count = count_arguments(token);
	ft_memset(new_cmd, 0, sizeof(t_cmd));
	new_cmd->argv = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_cmd->argv)
		return ;
	while (token && token->type != PIPE)
	{
		if (token->type == INPUT)
		{
			set_value(&new_cmd->infile, ft_strdup(token->next->name));
			set_value(&new_cmd->limiter, NULL);
		}
		else if (token->type == HEREDOC)
		{
			set_value(&new_cmd->infile, name_heredoc_file());
			set_value(&new_cmd->limiter, ft_strdup(token->next->name));
		}
		else if (token->type == TRUNC || token->type == APPEND)
			set_value(&new_cmd->outfile, ft_strdup(token->next->name));
		new_cmd->heredoc = token->type == HEREDOC;
		new_cmd->append = token->type == APPEND;
		token = token->next;
	}
}

static t_cmd	*get_cmd(t_token **current)
{
	t_cmd	*new_cmd;
	int		i;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	init_cmd(new_cmd, (*current));
	new_cmd->redirections = handle_redirections((*current), new_cmd);
	i = 0;
	while ((*current) && (*current)->type != PIPE)
	{
		if ((*current)->type == CMD || (*current)->type == ARGUMENT
			|| (*current)->type == EMPTY)
		{
			new_cmd->argv[i] = ft_strdup((*current)->name);
			if (!new_cmd->argv[i])
				return (free_cmd(new_cmd), NULL);
			i++;
		}
		(*current) = (*current)->next;
	}
	new_cmd->argv[i] = NULL;
	return (new_cmd);
}

t_cmd	*create_cmd(t_obj *obj)
{
	t_token	*current;
	t_cmd	*head;
	t_cmd	*new_cmd;

	current = obj->token;
	head = get_cmd(&current);
	if (!head)
		return (NULL);
	while (current)
	{
		current = current->next;
		new_cmd = get_cmd(&current);
		if (!new_cmd)
			return (free_cmd(head), NULL);
		append_cmd(head, new_cmd);
	}
	return (head);
}
