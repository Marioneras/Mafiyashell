/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:52:49 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/14 13:02:03 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_signal_exit_code(int signal)
{
	if (signal == SIGINT)
		return (130);
	else if (signal == SIGQUIT)
		return (131);
	return (128 + signal);
}

static int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (get_signal_exit_code(WTERMSIG(status)));
	return (0);
}

static int	wait_for_child(pid_t pid)
{
	int	status;

	if (pid == -1)
		return (0);
	if (waitpid(pid, &status, 0) == -1)
		return (0);
	return (status);
}

void    wait_for_all(int number_of_commands, t_obj *obj)
{
    int i;
    int status;
	int	exit_status;
	int	last_status;

    i = -1;
    status = 0;
	exit_status = 0;
	last_status = 0;
    while (++i < number_of_commands)
    {
        if (obj->pid[i] != -1)
		{
			status = wait_for_child(obj->pid[i]);
			if (obj->pid[i] == obj->pid[number_of_commands - 1])
				last_status = status;
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				exit_status = 130;
			else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				exit_status = 131;
		}
	}
	if (exit_status == 0)
		exit_status = get_exit_status(last_status);
	obj->exit_code = exit_status;
}
