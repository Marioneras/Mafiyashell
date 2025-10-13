/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:40:39 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 19:42:28 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_cmd *current)
{
	int	number_of_commands;

	number_of_commands = 0;
	while (current)
	{
		number_of_commands++;
		current = current->next;
	}
	return (number_of_commands);
}

void	dup_files(t_cmd *cmd, int input_fd, int output_fd, int *pipe_fd)
{
	if (cmd->infile || input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) < 0)
			display_error_message(errno, cmd->infile);
		close(input_fd);
	}
	if (cmd->next && !cmd->outfile)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			display_error_message(errno, "pipe");
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	if (cmd->outfile)
	{
		if (dup2(output_fd, STDOUT_FILENO) < 0)
			display_error_message(errno, cmd->outfile);
		close(output_fd);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

void	reset_offset(int *input_fd, char *infile)
{
	close(*input_fd);
	*input_fd = open(infile, O_RDWR | O_EXCL, 0600);
	if (*input_fd < 0)
	{
		display_error_message(errno, infile);
		exit(127);
	}
	if (unlink(infile) < 0)
		display_error_message(errno, infile);
}

int	execute_alone_redirections(t_obj *obj, int i, int *input_fd)
{
	obj->pid[i] = -1;
	if (obj->cmd->heredoc)
	{
		close(*input_fd);
		*input_fd = 0;
		if (unlink(obj->cmd->infile) < 0)
			display_error_message(errno, obj->cmd->infile);
	}
	return (0);
}

void	close_fd(t_cmd *cmd, int *input_fd, int output_fd, int pipe_fd[2])
{
	int	old_fd;

	if (cmd->infile)
		close(*input_fd);
	if (cmd->outfile)
		close(output_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		old_fd = *input_fd;
		*input_fd = pipe_fd[0];
		if (old_fd != STDIN_FILENO)
			close(old_fd);
	}
}
