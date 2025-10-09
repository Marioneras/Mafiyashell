/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:07:26 by mberthou          #+#    #+#             */
/*   Updated: 2025/09/08 11:43:23 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(char *filename, int type)
{
	int	fd;

	if (type == INPUT)
		fd = open(filename, O_RDONLY);
	else if (type == TRUNC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		display_error_message(errno, filename);
	return (fd);
}

bool	open_fd(t_obj *obj, t_cmd *cmd, int *input_fd, int *output_fd)
{
	if (cmd->infile && cmd->heredoc)
		*input_fd = here_doc(obj, cmd->infile, cmd->limiter);
	if (cmd->infile && !cmd->heredoc)
		*input_fd = open(cmd->infile, O_RDONLY);
	if (cmd->outfile && cmd->append)
		*output_fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (cmd->outfile && !cmd->append)
		*output_fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*input_fd < 0)
		return (display_error_message(errno, cmd->infile), false);
	if (*input_fd == 130 || *input_fd == 131 || *input_fd == 150)
		return (false);
	if (*output_fd < 0)
		return (display_error_message(errno, cmd->outfile), false);
	return (true);
}

bool	create_files(t_obj *obj)
{
	int				tmp_file;
	t_cmd			*current_cmd;
	t_redirections	*current_red;

	current_cmd = obj->cmd;
	while (current_cmd)
	{
		current_red = current_cmd->redirections;
		while (current_red)
		{
			if (current_red->type == HEREDOC)
			{
				tmp_file = here_doc(obj, current_red->name, current_red->limiter);
				if (tmp_file < 0 || tmp_file == 130 || tmp_file == 131)
					return (false);
				close(tmp_file);
				unlink(current_red->name);
			}
			else if (open_file(current_red->name, current_red->type) < 0)
				return (false);
			current_red = current_red->next;
		}
		current_cmd = current_cmd->next;
	}
	return (true);
}

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

static bool	is_end_of_pipeline(t_token *current)
{
	if (!current || !current->next)
		return (false);
	if (current->next->type == PIPE)
		return (true);
	if (current->next->next
		&& current->next->type == LIMITER
		&& current->next->next->type == PIPE)
		return (true);
	if (!current->next->next)
		return (true);
	return (false);
}

static bool is_last_infile_or_outfile(t_cmd *cmd, t_token *token)
{
	if (!token->next)
		return (true);
	if (token->type != HEREDOC
		&& ft_strncmp(cmd->infile, token->next->name, ft_strlen(cmd->infile) + 1) == 0)
		return (true);
	else if (token->type == HEREDOC
		&& ft_strncmp(cmd->limiter, token->next->name, ft_strlen(cmd->limiter) + 1) == 0)
		return (true);
	if (ft_strncmp(cmd->outfile, token->next->name, ft_strlen(cmd->outfile) + 1) == 0)
		return (true);
	return (false);
}

t_redirections	*handle_redirections(t_token *token, t_cmd *current_cmd)
{
	t_token			*current;
	t_redirections	*head;
	t_redirections	*new_red;

	current = token;
	while ((current && (current->type != INPUT && current->type != APPEND
			&& current->type != TRUNC && current->type != HEREDOC)))
				current = current->next;
	if (!current)
		return (NULL);
	if (is_end_of_pipeline(current)
		|| is_last_infile_or_outfile(current_cmd, current))
		return (NULL);
	head = get_redirection(current);
	if (!head)
		return (NULL);
	current = current->next;
	while (current && current->type != PIPE)
	{
		if ((current->type == INPUT || current->type == APPEND
			|| current->type == TRUNC || current->type == HEREDOC)
			&& (current->next && current->next->type != PIPE))
		{
			if (!is_last_infile_or_outfile(current_cmd, current))
			{
				new_red = get_redirection(current);
				if (!new_red)
					return (free_redirections(head), NULL);
				append_redirections(head, new_red);
			}
		}
		current = current->next;
	}
	return (head);
}

void	set_redirections(t_obj *obj, int *infile, int *outfile)
{
	if (obj->cmd->infile)
	{
		*infile = open(obj->cmd->infile, O_RDONLY);
		if (*infile < 0)
			exit(127);
		if (dup2(*infile, STDIN_FILENO) < 0)
			display_error_message(errno, obj->cmd->infile);
	}
	if (obj->cmd->outfile)
	{
		if (obj->cmd->append)
			*outfile = open(obj->cmd->outfile, O_CREAT | O_WRONLY | O_APPEND,
					0644);
		else
			*outfile = open(obj->cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC,
					0644);
		if (*outfile < 0)
			exit(127);
		if (dup2(*outfile, STDOUT_FILENO) < 0)
			display_error_message(errno, obj->cmd->outfile);
	}
}
