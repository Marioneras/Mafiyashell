/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:48:40 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/13 17:08:48 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*calloc;

	calloc = malloc(nmemb * size);
	if (!calloc)
		return (NULL);
	ft_bzero(calloc, nmemb * size);
	return (calloc);
}

/*#include <stdio.h>

int	main(void)
{
	int	*ptr;

	// This pointer will hold the
	// base address of the block created
	int n, i;
	// Get the number of elements for the array
	n = 5;
	printf("Enter number of elements: %d\n", n);
	// Dynamically allocate memory using calloc()
	ptr = (int *)ft_calloc(n, sizeof(int));
	// Check if the memory has been successfully
	// allocated by calloc or not
	if (ptr == NULL)
	{
		printf("Memory not allocated.\n");
		exit(0);
	}
	else
	{
		// Memory has been successfully allocated
		printf("Memory successfully allocated using calloc.\n");
		// Get the elements of the array
		for (i = 0; i < n; ++i)
		{
			ptr[i] = i + 1;
		}
		// Print the elements of the array
		printf("The elements of the array are: ");
		for (i = 0; i < n; ++i)
		{
			printf("%d, ", ptr[i]);
		}
	}
	return (0);
}*/
