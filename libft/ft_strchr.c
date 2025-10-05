/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:43:07 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/13 14:49:36 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*str;
	unsigned char	ch;

	str = (char *)s;
	ch = (unsigned char)c;
	while (*str)
	{
		if (*str == ch)
			return (str);
		str++;
	}
	if (ch == '\0')
		return (str);
	return (NULL);
}

/*#include <stdio.h>

int	main(void)
{
	const char	*str;
	int			c;

	str = "Je suis stud a 42";
	c = 'u';
	printf("%s\n", ft_strchr(str, c)); // should print "uis stud a 42"
	c = 'z';
	printf("%s\n", ft_strchr(str, c)); // should print "(null)"
	c = '\0';
	printf("%s\n", ft_strchr(str, c)); // should print ""
	return (0);
}*/
