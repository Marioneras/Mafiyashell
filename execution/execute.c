/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:12:59 by mberthou          #+#    #+#             */
/*   Updated: 2025/09/27 10:44:40 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			display_error_message(errno, "pipe"); // check for the right message
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	if (cmd->outfile)
	{
		if (dup2(output_fd, STDOUT_FILENO) < 0)
			display_error_message(errno, cmd->outfile);
		close(output_fd);
	}
}

static int	child_process(t_obj *obj, int input_fd, int output_fd, int *pipe_fd)
{
	char	*cmd_path;
	int		(*builtin)(t_obj *obj);

	child_signal();
	if (obj->cmd->heredoc)
	{
		close(input_fd);
		input_fd = open(".heredoc", O_RDWR | O_EXCL, 0600);
		if (input_fd < 0)
			return (display_error_message(errno, ".heredoc"), 127);
		if (unlink(".heredoc") < 0)
			display_error_message(errno, ".heredoc");
	}
	dup_files(obj->cmd, input_fd, output_fd, pipe_fd);
	builtin = is_builtin(obj->cmd->argv[0]);
	if (builtin)
		builtin(obj);
	else
	{
		cmd_path = get_absolute_path(obj->cmd, obj->env);
		if (!cmd_path)
		{
			free(obj->pid);
			free_obj(obj);
			exit (126);
		}
		if (execve(cmd_path, obj->cmd->argv, obj->env) < 0)
		{
			display_error_message(errno, obj->cmd->argv[0]);
			exit (127);
		}
	}
	exit (obj->exit_code);
}

static int	execute_command(t_obj *obj, int i, int *input_fd)
{
	int	pipe_fd[2];
	int	output_fd;

	output_fd = STDOUT_FILENO;
	open_fd(obj->cmd, input_fd, &output_fd, obj->env);
	if (obj->cmd->next)
	{
		if (pipe(pipe_fd) < 0)
				return (127);
	}
	obj->pid[i] = fork();
	if (obj->pid[i] == 0)
		child_process(obj, *input_fd, output_fd, pipe_fd);
	else if (obj->pid[i] < 0)
		return (127);
	if (obj->cmd->infile)
		close(*input_fd);
	if (obj->cmd->next)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
	return (0);
}

static void	wait_for_all(int number_of_commands, t_obj *obj)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < number_of_commands)
	{
		if (i + 1 == number_of_commands)
			waitpid(obj->pid[i], &status, 0);
		else
			waitpid(obj->pid[i], NULL, 0);
		i++;
	}
	if (g_signal == SIGQUIT)
	{
    	obj->exit_code = 128 + SIGQUIT; // 131
    	g_signal = 0;
	}
	if (WIFEXITED(status))
		obj->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
        obj->exit_code = 128 + WTERMSIG(status); // Gère les terminaisons par signal (ex. SIGINT)
	free(obj->pid);
}

static void	execution_routine(t_obj *obj)
{
	int		i;
	int		number_of_commands;
	int		input_fd;
	t_cmd	*current;

	input_fd = STDIN_FILENO;
	current = obj->cmd;
	number_of_commands = 0;
	while (current)
	{
		number_of_commands++;
		current = current->next;
	}
	obj->pid = (int *)malloc(sizeof(int) * number_of_commands);
	if (!obj->pid)
		exit(127);
	i = -1;
	while (obj->cmd)
	{
		obj->exit_code = execute_command(obj, ++i, &input_fd);
		obj->cmd = obj->cmd->next;
	}
	close(input_fd);
	wait_for_all(number_of_commands, obj);
}

void	execute(t_obj *obj)
{
	t_cmd	*saved_cmd;

	in_exec_signal();
	if (create_files(obj))
	{
		saved_cmd = obj->cmd;
		if (!obj->cmd->next && is_builtin(obj->cmd->argv[0]))
		{
			run_single_builtin_safely(obj);
			// check if builtin execution worked
		}
		else
			execution_routine(obj);
		free_cmd(saved_cmd);
	}
	else
	{
		obj->exit_code = 1;
		free_cmd(obj->cmd);
	}
	free(obj->input);
	normal_signal();
}
