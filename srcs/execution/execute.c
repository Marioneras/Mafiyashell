/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:12:59 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/14 13:02:22 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_process(t_obj *obj, int input_fd, int output_fd, int *pipe_fd)
{
	char	*cmd_path;
	int		(*builtin)(t_obj *obj);

	child_signal();
	if (obj->cmd->heredoc)
		reset_offset(&input_fd, obj->cmd->infile);
	dup_files(obj->cmd, input_fd, output_fd, pipe_fd);
	builtin = is_builtin(obj->cmd->argv[0]);
	if (!builtin)
	{
		cmd_path = get_absolute_path(obj->cmd, obj->env);
		if (!cmd_path)
		{
			free_obj(obj);
			exit(127);
		}
		execve(cmd_path, obj->cmd->argv, obj->env);
		display_error_message(errno, obj->cmd->argv[0]);
		free(cmd_path);
		free_obj(obj);
		exit(126);
	}
	obj->exit_code = builtin(obj);
	free_obj(obj);
	exit(0);
}

static int	execute_command(t_obj *obj, int i, int *input_fd)
{
	int	pipe_fd[2];
	int	output_fd;
	int	error_code;

	output_fd = STDOUT_FILENO;
	error_code = open_fd(obj, obj->cmd, input_fd, &output_fd);
	if (error_code != 0)
		return (error_code);
	if (!obj->cmd->argv[0])
		return (execute_alone_redirections(obj, i, input_fd, output_fd));
	if (obj->cmd->next)
		if (pipe(pipe_fd) < 0)
			return (127);
	obj->pid[i] = fork();
	if (obj->pid[i] == 0)
		child_process(obj, *input_fd, output_fd, pipe_fd);
	else if (obj->pid[i] < 0)
		return (127);
	close_fd(obj->cmd, input_fd, output_fd, pipe_fd);
	return (0);
}

static void	execution_routine(t_obj *obj)
{
	int		i;
	int		number_of_commands;
	int		input_fd;
	t_cmd	*current;

	input_fd = STDIN_FILENO;
	current = obj->cmd;
	number_of_commands = count_cmds(current);
	obj->pid = (int *)ft_calloc(sizeof(int), number_of_commands);
	if (!obj->pid)
		exit(127);
	i = -1;
	while (obj->cmd)
	{
		obj->exit_code = execute_command(obj, ++i, &input_fd);
		obj->cmd = obj->cmd->next;
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (obj->exit_code != 1 && obj->exit_code != 130 && obj->exit_code != 131)
		wait_for_all(number_of_commands, obj);
}

void	execute(t_obj *obj)
{
	int		error_code;
	t_cmd	*saved_cmd;

	in_exec_signal();
	error_code = create_files(obj);
	if (error_code == 0)
	{
		saved_cmd = obj->cmd;
		if (!obj->cmd->next && is_builtin(obj->cmd->argv[0]))
			run_single_builtin_safely(obj);
		else
			execution_routine(obj);
		free_cmd(saved_cmd);
	}
	else
	{
		obj->exit_code = error_code;
		free_cmd(obj->cmd);
	}
	ft_clear((char **)&obj->pid);
	free(obj->input);
	normal_signal();
}
