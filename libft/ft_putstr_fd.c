/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:59:55 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/15 16:42:06 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * the fd parameter represents the file descriptor to which the string s will/
 *  be written. It allows the function to write the content of the string to/
 *  a specific output destination, whether it's a file, a terminal, /
 * or another communication channel. 
 */

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = ft_strlen(s);
	write (fd, s, i);
}
