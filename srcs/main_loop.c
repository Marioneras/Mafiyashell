/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:36:22 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/06 15:37:02 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_obj(t_obj *obj, char **env)
{
	obj->token = NULL;
	obj->cmd = NULL;
	obj->env = env;
	if (getcwd(obj->tool.pwd, sizeof(obj->tool.pwd)) == NULL
		|| getcwd(obj->tool.old_pwd, sizeof(obj->tool.pwd)) == NULL)
	{
		perror("getcwd() error");
		exit(2);
	}
	obj->fd.save_stdin = -1;
	obj->fd.save_stdout = -1;
	obj->fd.infile = -1;
	obj->fd.outfile = -1;
	obj->input = NULL;
	obj->pid = 0;
	obj->exit_code = 0;
}

char	**safe_env(void)
{
	char **tab;
	char *pwd;

	tab = malloc(sizeof(char *) * 5);
	if (!tab)
		return (NULL);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(tab), NULL);
	tab[0] = ft_strjoin("PWD=", pwd);
	if (!tab[0])
		return(free(pwd), free_tab(tab, 0), NULL);
	tab[1] = ft_strdup("SHLVL=1");
	if (!tab[1])
		return(free(pwd), free_tab(tab, 1), NULL);
	tab[2] = ft_strdup("_=/usr/bin/env");
	if (!tab[2])
		return(free(pwd), free_tab(tab, 2), NULL);
	tab[3] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/sbin:/usr/sbin");
	tab[4] = NULL;
	free(pwd);
	return (tab);
}

int main(int argc, char *argv[], char **envp)
{
	t_obj obj;
	(void)argc;
	(void)argv;
	char **cenvp;

	if (!envp || !envp[0])
		cenvp = safe_env();
	else
		cenvp = clone_env(envp);
	init_obj(&obj, cenvp);
	normal_signal();
	if (argc == 1)
	{
		clear_history();
		while (42)
		{
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
			if (g_signal == SIGINT)
				obj.exit_code = 130;
			if (obj.input[0] && obj.input[0] != '\0')
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
