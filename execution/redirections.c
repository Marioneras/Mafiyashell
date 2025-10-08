/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:07:26 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 18:41:06 by mberthou         ###   ########.fr       */
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
	t_cmd			*cur_cmd;
	t_redirections	*cur_red;

	cur_cmd = obj->cmd;
	while (cur_cmd)
	{
		cur_red = cur_cmd->redirections;
		while (cur_red)
		{
			if (cur_red->type == HEREDOC)
			{
				tmp_file = here_doc(obj, cur_red->name, cur_red->limiter);
				if (tmp_file < 0 || tmp_file == 130 || tmp_file == 131)
					return (false);
				close(tmp_file);
				unlink(cur_red->name);
			}
			else if (open_file(cur_red->name, cur_red->type) < 0)
				return (false);
			cur_red = cur_red->next;
		}
		cur_cmd = cur_cmd->next;
	}
	return (true);
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
