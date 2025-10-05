/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:43:53 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/13 16:00:37 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	str1 = (char *)s1;
	str2 = (char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n && str1[i] == str2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

/*#include <stdio.h>

int	main(void)
{
	const void	*str1;
	const void	*str2;

	str1 = "Je suis stud a 42";
	str2 = "Je suis stud a 43";
	printf("%d\n", ft_memcmp(str1, str2, 16));
	printf("%d", ft_memcmp(str1, str2, 15));
}*/
