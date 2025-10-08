/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:46:19 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 19:47:48 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_sep(char c, char *token, bool track_s_quote, bool track_d_quote)
{
	if (!token)
		return (false);
	if ((c == '\'' || c == '"') && (*token == '|' || *token == '<'
			|| *token == '>'))
		return (true);
	if (track_s_quote || track_d_quote)
		return (false);
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (true);
	if ((c == '|' || c == '<' || c == '>') && (*token != '|' && *token != '<'
			&& *token != '>'))
		return (true);
	if ((c != '|' && c != '<' && c != '>') && (*token == '|' || *token == '<'
			|| *token == '>'))
		return (true);
	else
		return (false);
}

void	track_quotes(char c, bool *s_quote, bool *d_quote)
{
	if (c == '"' && (!*d_quote && !*s_quote))
		*d_quote = true;
	else if (c == '\'' && (!*s_quote && !*d_quote))
		*s_quote = true;
	else if (c == '"' && *d_quote)
		*d_quote = false;
	else if (c == '\'' && *s_quote)
		*s_quote = false;
}
