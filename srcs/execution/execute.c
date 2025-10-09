/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:12:59 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 19:42:26 by mberthou         ###   ########.fr       */
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
			ft_clear_tab(obj->env);
			free_obj(obj);
			exit(126);
		}
		execve(cmd_path, obj->cmd->argv, obj->env);
		display_error_message(errno, obj->cmd->argv[0]);
		exit(127);
	}
	obj->exit_code = builtin(obj);
	ft_clear_tab(obj->env);
	free_obj(obj);
	exit(0);
}

static int	execute_command(t_obj *obj, int i, int *input_fd)
{
	int	pipe_fd[2];
	int	output_fd;

	output_fd = STDOUT_FILENO;
	if (!open_fd(obj, obj->cmd, input_fd, &output_fd))
		return (1);
	if (!obj->cmd->argv[0])
		return (execute_alone_redirections(obj, i, *input_fd));
	if (obj->cmd->next)
		if (pipe(pipe_fd) < 0)
			return (127);
	obj->pid[i] = fork();
	if (obj->pid[i] == 0)
		child_process(obj, *input_fd, output_fd, pipe_fd);
	else if (obj->pid[i] < 0)
		return (127);
	close_fd(obj->cmd, input_fd, pipe_fd);
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
		if (obj->pid[i] == -1)
			;
		else if (i + 1 == number_of_commands)
			waitpid(obj->pid[i], &status, 0);
		else
			waitpid(obj->pid[i], NULL, 0);
		i++;
	}
	if (g_signal == SIGQUIT)
	{
		obj->exit_code = 128 + SIGQUIT;
		g_signal = 0;
	}
	if (WIFEXITED(status))
		obj->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		obj->exit_code = 128 + WTERMSIG(status);
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
	obj->pid = (int *)malloc(sizeof(int) * number_of_commands);
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
	if (obj->exit_code != 1)
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
			run_single_builtin_safely(obj);
		else
			execution_routine(obj);
		free_cmd(saved_cmd);
	}
	else
	{
		obj->exit_code = 1;
		free_cmd(obj->cmd);
	}
	ft_clear((char **)&obj->pid);
	free(obj->input);
	normal_signal();
}
