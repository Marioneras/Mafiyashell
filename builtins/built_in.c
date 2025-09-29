/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:57:01 by mberthou          #+#    #+#             */
/*   Updated: 2025/09/13 18:02:10 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_built_in(t_cmd *cmd)
{
	if (!cmd->argv[0])
		return (false);
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (true);
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (true);
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (true);
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (true);
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (true);
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (true);
	return (false);
}

static void run_exit(t_obj *obj)
{
	int exit_code;

	exit_code = obj->exit_code;
	printf("exit\n");
	free_obj(obj);
	clear_history();
	exit(exit_code);
}

void run_builtin(t_obj *obj, t_cmd *cmd, int infile, int outfile)
{
	(void)infile;
	(void)outfile;

	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		ft_echo(cmd->argv);
	else if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		run_cd(obj);
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		run_pwd(obj);
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		run_export(obj);
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		run_unset(obj);
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		run_env(obj);
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		run_exit(obj);
}

int run_single_builtin_safely(t_obj *obj)
{
	int save_stdin;
	int save_stdout;
	int infile;
	int outfile;

	infile = 0;
	outfile = 1;
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	set_redirections(obj, &infile, &outfile);
	run_builtin(obj, obj->cmd, infile, outfile);
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	if (save_stdin >= 0)
		close(save_stdin);
	if (save_stdout >= 0)
		close(save_stdout);
	if (infile != -1 && infile != STDIN_FILENO)
		close(infile);
	if (outfile != -1 && outfile != STDOUT_FILENO)
		close(outfile);
	return (0);
}
