/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:39:30 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/13 14:17:27 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dst;
	char	*s;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	dst = (char *)dest;
	s = (char *)src;
	if (dst > s)
	{
		while (n-- > 0)
			dst[n] = s[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dst[i] = s[i];
			i++;
		}
	}
	return (dest);
}

/*int	main(void)
{
	char	csrc[100];

	csrc[100] = "stud42";
	ft_memmove(csrc + 5, csrc, ft_strlen(csrc) + 1);
	printf("%s", csrc);
	return (0);
}*/
