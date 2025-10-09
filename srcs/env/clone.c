/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 22:42:08 by safamran          #+#    #+#             */
/*   Updated: 2025/10/09 22:42:10 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab, int i)
{
	int	a;

	a = 0;
	while (a < i)
	{
		free(tab[a]);
		a++;
	}
	free(tab);
}

char	**clone_env(char **envp)
{
	char	**clone;
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	clone = malloc(sizeof(char *) * (i + 1));
	if (!clone)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		clone[i] = ft_strdup(envp[i]);
		if (!clone[i])
		{
			free_tab(clone, i);
			return (NULL);
		}
		i++;
	}
	clone[i] = NULL;
	return (clone);
}
/*
int	main(int ac, char **av, char **envp)
{
	char	**test;
	int		i;

	(void)ac;
	(void)av;
	test = clone_env(envp);
	i = 0;
	while (test[i] != NULL)
	{
		printf("%s\n", test[i]);
		i++;
	}
	free_tab(test, i);
	return (0);
}
*/
