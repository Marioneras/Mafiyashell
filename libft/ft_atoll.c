/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:06:51 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/10 16:28:13 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(char *str)
{
	int			i;
	int			sign;
	char		*err;
	long long	result;

	i = ((result = 0));
	sign = 1;
	err = "numeric argument required : ";
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if ((sign == 1 && result > LLONG_MAX) || (sign == -1
				&& result > LLONG_MAX))
			return (ft_putstr_fd(err, 2), ft_putstr_fd(str, 2), 2);
		i++;
	}
	return (result * sign);
}
