/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:36:19 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/12 16:57:29 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dst;
	char	*s;

	if (!dest && !src)
		return (NULL);
	dst = (char *)dest;
	s = (char *)src;
	while (n-- > 0)
		dst[n] = s[n];
	return (dest);
}

/*#include <string.h>
#include <unistd.h>

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	main(void)
{
	char	str1[] = "Salut";
	char	str2[] = "42";

	ft_putstr("str1 before memcpy : ");
	ft_putstr(str1);
	// Copies contents of str2 to str1
	ft_memcpy(str1, str2, sizeof(str2));
	ft_putstr("\nstr1 after memcpy : ");
	ft_putstr(str1);
	return (0);
}*/
