/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:36:22 by mberthou          #+#    #+#             */
/*   Updated: 2025/09/13 16:04:21 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ctrl_c(int signal, siginfo_t *info, void *contex)
{
	(void)signal;
	(void)info;
	(void)contex;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void init_signal()
{
	struct sigaction sa;
	sa.sa_sigaction = ctrl_c;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

static void init_obj(t_obj *obj, char **env)
{
	obj->token = NULL;
	obj->cmd = NULL;
	obj->env = env;
	obj->tool = (t_tool *)malloc(sizeof(t_tool));
	if (!obj->tool)
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
	if (argc == 1)
	{
		init_signal();
		clear_history();
		while (42)
		{
			init_signal();
			obj.input = readline("mafiyashell> "); // readline renvoie str alloue (=ce que user a ecrit)
			if (!obj.input)
				return (EXIT_FAILURE);
			add_history(obj.input);
			if (parsing(&obj, cenvp))
				execute(&obj);
		}
	}
	ft_freetab(obj.env);
	return (obj.exit_code);
}