/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_linked_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:53:22 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 19:53:39 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->name)
		{
			free(tmp->name);
			tmp->name = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	free_redirections(t_redirections *red)
{
	t_redirections	*tmp;

	while (red)
	{
		tmp = red;
		red = red->next;
		ft_clear(&tmp->name);
		if (tmp->limiter)
			ft_clear(&tmp->limiter);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		i = 0;
		while (tmp->argv[i])
		{
			free(tmp->argv[i]);
			tmp->argv[i] = NULL;
			i++;
		}
		free(tmp->argv);
		if (tmp->infile)
			ft_clear(&tmp->infile);
		if (tmp->outfile)
			ft_clear(&tmp->outfile);
		if (tmp->limiter)
			ft_clear(&tmp->limiter);
		free_redirections(tmp->redirections);
		free(tmp);
	}
}

void	free_obj(t_obj *obj)
{
	if (obj->cmd)
		free_cmd(obj->cmd);
	if (obj->input)
		free(obj->input);
	if (obj->pid)
		ft_clear((char **)&obj->pid);
}
