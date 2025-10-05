/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:01:47 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/13 16:30:56 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	*to_find;

	i = 0;
	str = (char *)big;
	to_find = (char *)little;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == to_find[j] && to_find[j] && i + j < len)
		{
			j++;
		}
		if (to_find[j] == '\0')
			return (&str[i]);
		i++;
	}
	return (0);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	*largestring;
	const char	*smallstring;
	char		*our_function;
//	char		*the_real_function;

	largestring = "oh no not the empty string !";
	smallstring = "";
	our_function = ft_strnstr(largestring, smallstring, 0);
	//the_real_function = strnstr(largestring, smallstring, 0);
	printf("our_function: %s\n", our_function);
	//printf("the_real_function: %s\n", the_real_function);
	return (0);
}*/
