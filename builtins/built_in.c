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

static int run_exit(t_obj *obj)
{
	int exit_code;
	int fd;

	exit_code = obj->exit_code;
	printf("exit\n");
	// if (fd->save_stdin >= 0)
	// 	close(fd->save_stdin);
	// if (fd->save_stdout >= 0)
	// 	close(fd->save_stdout);
	// if (fd->infile != -1 && fd->infile != STDIN_FILENO)
	// 	close(fd->infile);
	// if (fd->outfile != -1 && fd->outfile != STDOUT_FILENO)
	// 	close(fd->outfile);
	free_obj(obj);
	clear_history();
	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
	exit(exit_code);
	return (0);
}

int (*is_builtin(char *cmd))(t_obj *obj)
{
	const t_builtin dico[]= {
		(t_builtin){"echo", ft_echo},
		(t_builtin){"cd", run_cd},
		(t_builtin){"pwd", run_pwd},
		(t_builtin){"export", run_export},
		(t_builtin){"unset", run_unset},
		(t_builtin){"env", run_env},
		(t_builtin){"exit", run_exit},
		(t_builtin){0, 0}
	};
	int	i;

	i = -1;
	while (dico[++i].name)
		if (ft_strncmp(cmd, dico[i].name, ft_strlen(cmd) + 1) == 0)
			return (dico[i].function);
	return (0);
}

int run_single_builtin_safely(t_obj *obj)
{
	t_fd fd;
	int (*builtin)(t_obj *obj);

	fd.infile = 0;
	fd.outfile = 1;
	fd.save_stdin = dup(STDIN_FILENO);
	fd.save_stdout = dup(STDOUT_FILENO);
	set_redirections(obj, &fd.infile, &fd.outfile);
	builtin = is_builtin(obj->cmd->argv[0]);
	if (builtin)
		builtin(obj);
	dup2(fd.save_stdin, STDIN_FILENO);
	dup2(fd.save_stdout, STDOUT_FILENO);
	if (fd.save_stdin >= 0)
		close(fd.save_stdin);
	if (fd.save_stdout >= 0)
		close(fd.save_stdout);
	if (fd.infile != -1 && fd.infile != STDIN_FILENO)
		close(fd.infile);
	if (fd.outfile != -1 && fd.outfile != STDOUT_FILENO)
		close(fd.outfile);
	return (0);
}
