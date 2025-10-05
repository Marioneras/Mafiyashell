/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:55:17 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/12 11:00:00 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*dest;

	dest = (char *)s;
	while (n-- > 0)
		dest[n] = c;
	return (s);
}

/* #include <stdio.h>

int	main(void)
{
	char	str[50] = "Je suis etudiante a l'ecole 42";

	printf("\nBefore ft_memset(): %s\n", str);
	// Fill 8 characters starting from str[13] with '.'
	ft_memset(str, '.', 20 * sizeof(char));
	printf("After ft_memset():  %s", str);
	return (0);
}*/
