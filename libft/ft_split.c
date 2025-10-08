/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:14:58 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/19 18:16:31 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static size_t	ft_word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	ft_free_tab(char **tab, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**ft_fill_array(char **tab, char const *s, char c)
{
	size_t i, (j), (k);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[j] = malloc(sizeof(char) * (ft_word_len(&s[i], c) + 1));
			if (!tab[j])
			{
				ft_free_tab(tab, j);
				return (NULL);
			}
			k = 0;
			while (s[i] && s[i] != c)
				tab[j][k++] = s[i++];
			tab[j++][k] = '\0';
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	return (ft_fill_array(tab, s, c));
}

/*#include <stdio.h>
int	main(void)
{
  char **tab;
  int i;

  tab = ft_split("salut les amis", ' ');
  i = 0;
  while (tab[i])
  {
	printf("%s\n", tab[i]);
	i++;
  }
  return (0);
}*/
