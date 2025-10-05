/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:42:47 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/13 14:53:05 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*last;
	unsigned char	ch;

	last = NULL;
	ch = (unsigned char)c;
	while (*s)
	{
		if (*s == ch)
			last = (char *)s;
		s++;
	}
	if (*s == ch)
		last = (char *)s;
	return (last);
}

/*#include <stdio.h>

int	main(void)
{
	const char	str[17];
	int			c;

	str[17] = "Je suis stud a 42";
	c = 'u';
	printf("%s", ft_strrchr(str, c));
	return (0);
}*/
