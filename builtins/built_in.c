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

static int	run_exit(t_obj *obj)
{
	int	exit_code;

	ft_putstr_fd("exit\n", 1);
	if (obj->cmd->argv[1] && obj->cmd->argv[2])
		return (ft_putstr_fd("mafiyashell: exit: too many arguments\n", 2), 130);
	if (obj->cmd->argv[1] && !ft_strevery(obj->cmd->argv[1], ft_isdigit))
	{
		ft_putstr_fd("mafiyashell: ", 2);
		ft_putstr_fd(obj->cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		obj->exit_code = 2;
	}
	if (obj->fd.save_stdin >= 0)
		close(obj->fd.save_stdin);
	if (obj->fd.save_stdout >= 0)
		close(obj->fd.save_stdout);
	if (obj->fd.infile != -1 && obj->fd.infile != STDIN_FILENO)
		close(obj->fd.infile);
	if (obj->fd.outfile != -1 && obj->fd.outfile != STDOUT_FILENO)
		close(obj->fd.outfile);
	exit_code = obj->exit_code;
	free_obj(obj);
	clear_history();
	exit(exit_code);
	return (0);
}

int	(*is_builtin(char *cmd))(t_obj *obj)
{
	const t_builtin	dico[] =	{
		(t_builtin){"echo", ft_echo},
		(t_builtin){"cd", run_cd},
		(t_builtin){"pwd", run_pwd},
		(t_builtin){"export", run_export},
		(t_builtin){"unset", run_unset},
		(t_builtin){"env", run_env},
		(t_builtin){"exit", run_exit},
		(t_builtin){0, 0}
	};
	int				i;

	i = -1;
	while (dico[++i].name)
		if (ft_strncmp(cmd, dico[i].name, ft_strlen(cmd) + 1) == 0)
			return (dico[i].function);
	return (0);
}

int	run_single_builtin_safely(t_obj *obj)
{
	int	(*builtin)(t_obj *obj);

	obj->fd.infile = 0;
	obj->fd.outfile = 1;
	obj->fd.save_stdin = dup(STDIN_FILENO);
	obj->fd.save_stdout = dup(STDOUT_FILENO);
	set_redirections(obj, &obj->fd.infile, &obj->fd.outfile);
	builtin = is_builtin(obj->cmd->argv[0]);
	if (builtin)
		obj->exit_code = builtin(obj);
	dup2(obj->fd.save_stdin, STDIN_FILENO);
	dup2(obj->fd.save_stdout, STDOUT_FILENO);
	if (obj->fd.save_stdin >= 0)
		close(obj->fd.save_stdin);
	if (obj->fd.save_stdout >= 0)
		close(obj->fd.save_stdout);
	if (obj->fd.infile != -1 && obj->fd.infile != STDIN_FILENO)
		close(obj->fd.infile);
	if (obj->fd.outfile != -1 && obj->fd.outfile != STDOUT_FILENO)
		close(obj->fd.outfile);
	return (0);
}
