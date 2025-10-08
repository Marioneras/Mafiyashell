/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:06:30 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/13 17:33:11 by mberthou         ###   ########.fr       */
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
}

void	ft_clear_tab(char **tab)
{
	int	i;

	if (!tab || !*tab)
		return ;
	i = -1;
	while (tab[++i])
		ft_clear(&tab[i]);
	free(tab);
}

char	*ft_clear(char **array)
{
	if (*array)
	{
		free(*array);
		*array = NULL;
	}
	return (NULL);
}
