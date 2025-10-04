/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:36:22 by mberthou          #+#    #+#             */
/*   Updated: 2025/09/27 10:44:49 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_obj(t_obj *obj, char **env)
{
	obj->token = NULL;
	obj->cmd = NULL;
	obj->env = env;
	obj->fd = (t_fd *)malloc(sizeof(t_fd));
	obj->tool = (t_tool *)malloc(sizeof(t_tool));
	if (!obj->fd || !obj->tool)
		exit(2);
	if (getcwd(obj->tool->pwd, sizeof(obj->tool->pwd)) == NULL)
	{
		perror("getcwd() error");
		free(obj->tool);
		exit(2);
	}
	if (getcwd(obj->tool->old_pwd, sizeof(obj->tool->pwd)) == NULL)
	{
		perror("getcwd() error");
		free(obj->tool);
		exit(2);
	}
	obj->fd->save_stdin = -1;
	obj->fd->save_stdout = -1;
	obj->fd->infile = -1;
	obj->fd->outfile = -1;
	obj->input = NULL;
	obj->pid = 0;
	obj->exit_code = 0;
}

int main(int argc, char *argv[], char **envp)
{
	t_obj obj;
	(void)argc;
	(void)argv;
	char **cenvp;

	cenvp = clone_env(envp);
	init_obj(&obj, cenvp);
	normal_signal();
	if (argc == 1)
	{
		//init_signal();
		clear_history();
		while (42)
		{
			//init_signal();
			if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)
				|| !isatty(STDERR_FILENO))
				obj.input = get_next_line(STDIN_FILENO);
			else
				obj.input = readline("mafiyashell> ");
			if (!obj.input)
			{
				if (isatty(STDIN_FILENO))
				{
					write(STDOUT_FILENO, "exit\n", 5);
					ft_freetab(obj.env);
					return (EXIT_SUCCESS);
				}
				else
				{
					ft_freetab(obj.env);
					return (EXIT_FAILURE);
				}
			}
			add_history(obj.input);
			if (parsing(&obj))
				execute(&obj);
			g_signal = 0;
			normal_signal();
		}
	}
	ft_freetab(obj.env);
	return (obj.exit_code);
}
