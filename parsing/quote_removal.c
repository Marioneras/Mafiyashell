/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:02:06 by mberthou          #+#    #+#             */
/*   Updated: 2025/08/24 19:30:26 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool to_rm(char c, bool track_s_quote, bool track_d_quote)
{
	if ((c == '\'' && track_s_quote) || (c == '"' && track_d_quote))
		return (true);
	else if ((c != '\'' && track_s_quote) || (c != '"' && track_d_quote))
		return (false);
	else if ((c == '\'' && !track_s_quote) || (c == '"' && !track_d_quote))
		return (true);
	return (false);
}

static bool	found_quotes_to_remove(t_token token)
{
	bool	track_s_quotes;
	bool	track_d_quotes;
	int		i;

	track_s_quotes = false;
	track_d_quotes = false;
	i = 0;
	while (token.name[i])
	{
		track_quotes(token.name[i], &track_s_quotes, &track_d_quotes);
		if (to_rm(token.name[i], track_s_quotes, track_d_quotes))
			return (true);
		i++;
	}
	return (false);
}

char	*remove_quotes(char *str)
{
	char	*new_str;
	bool	track_s_quotes;
	bool	track_d_quotes;
	int		i;
	int		j;

	new_str = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	track_s_quotes = false;
	track_d_quotes = false;
	while (str[i])
	{
		track_quotes(str[i], &track_s_quotes, &track_d_quotes);
		if (!to_rm(str[i], track_s_quotes, track_d_quotes))
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	quote_removal(t_token *token)
{
	t_token	*current;
	char	*tmp;

	current = token;
	while (current)
	{
		if (found_quotes_to_remove(*current) && current->type != LIMITER)
		{
			tmp = current->name;
			current->name = remove_quotes(tmp);
			if (!current->name)
				return ;
			ft_clear(&tmp);
		}
		current = current->next;
	}
}
