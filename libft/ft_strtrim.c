/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:19:26 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/18 14:23:15 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isseparater(int c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	size;
	char	*dest;

	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1);
	while (ft_isseparater(s1[start], set) == 1)
		start++;
	while (end > start && ft_isseparater(s1[end - 1], set) == 1)
		end--;
	size = end - start;
	dest = malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s1[start], size + 1);
	return (dest);
}

/*#include <stdio.h>

int	main(int ac, char **av)
{
	char	*str;

	if (ac != 3)
		return (-1);
	str = ft_strtrim(av[1], av[2]);
	printf("%s", str);
	free(str);
	return (0);
}*/
