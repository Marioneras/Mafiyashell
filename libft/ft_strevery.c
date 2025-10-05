/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strevery.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:08:12 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/05 18:15:38 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strevery(char *str, int (*f)(int))
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(f)((int)str[i]))
			return (false);
		i++;
	}
	return (true);
}
