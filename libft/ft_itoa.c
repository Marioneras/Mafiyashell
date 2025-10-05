/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:40:01 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/18 17:08:35 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(long nb)
{
	int	size;

	size = 0;
	if (nb == 0)
		size = 1;
	if (nb < 0)
	{
		nb *= -1;
		size++;
	}
	while (nb > 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		size;
	char	*dest;

	nb = n;
	size = ft_size(nb);
	dest = ft_calloc(size + 1, sizeof(char));
	if (!dest)
		return (NULL);
	dest[size] = '\0';
	if (nb < 0)
	{
		dest[0] = '-';
		nb = -nb;
	}
	while (size-- > 0)
	{
		if (dest[size] == '-')
			break ;
		dest[size] = nb % 10 + '0';
		nb /= 10;
	}
	return (dest);
}

/*#include <stdio.h>

int	main(int ac, char **av)
{
	char	*dest;

	if (ac > 2)
		return (-1);
	dest = ft_itoa(atoi(av[1]));
	printf("%s", dest);
	return (0);
}*/
