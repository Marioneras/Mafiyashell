/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:24:44 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/14 12:33:52 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (len-- > 0)
	{
		substr[i] = s[start + i];
		i++;
	}
	return (substr);
}

/*#include <stdio.h>

int	main(int ac, char **av)
{
	char	*str;

	if (ac != 4)
		return (-1);
	str = ft_substr(av[1], atoi(av[2]), (size_t)atoi(av[3]));
	printf("%s", str);
	free(str);
	return (0);
}*/
