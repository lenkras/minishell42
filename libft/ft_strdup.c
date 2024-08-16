/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:27:32 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/29 15:06:44 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 *  The strdup() function allocates sufficient memory for a copy of the
     string s1, does the copy, and returns a pointer to it. 
 * if insufficient memory is available, NULL is returned.
 */

char	*ft_strdup(const char *src)
{
	int		len;
	int		i;
	char	*newstr;

	len = ft_strlen(src);
	i = 0;
	newstr = ((char *)malloc(sizeof(char) * (len + 1)));
	if (newstr == NULL)
	{
		free(newstr);
		newstr = NULL;
		return (0);
	}
	while (src[i])
	{
		newstr[i] = src[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
