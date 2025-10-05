/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:26:58 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/13 13:41:29 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dest_len)
		return (dstsize + src_len);
	i = 0;
	while (src[i] && dest_len + i < dstsize - 1)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	first[8];
	char	last[25];
	int		r;
	int		size;
	char	buffer[33];

	first[8] = "This is ";
	last[25] = "a potentially long string";
	size = 33;
	strcpy(buffer, first);
	r = ft_strlcat(buffer, last, size);
	ft_putstr(buffer, 1);
	printf("Value returned: %d\n", r);
	if (r > size)
		ft_putstr("String truncated", 1
	else
		ft_putstr("String was fully copied", 1);
	return (0);
}*/
