/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:50:28 by epolkhov          #+#    #+#             */
/*   Updated: 2023/11/16 13:39:32 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The calloc() function contiguously allocates enough space for count
     objects that are size bytes of memory each and returns a pointer to the
     allocated memory.  The allocated memory is filled with bytes of value
     zero.
 */

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;
	size_t	total_size;
	size_t	max;

	max = SIZE_MAX;
	if (count > 0 && max / count < size)
		return (NULL);
	total_size = count * size;
	memory = (void *)malloc(total_size);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, total_size);
	return (memory);
}
