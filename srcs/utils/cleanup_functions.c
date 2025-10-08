/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:06:30 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 19:53:41 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
