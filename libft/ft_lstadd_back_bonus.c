/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:19:51 by epolkhov          #+#    #+#             */
/*   Updated: 2023/11/14 18:19:56 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*newnode;

	newnode = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	if (lst == NULL || new == NULL)
		return ;
	else
	{
		while (newnode -> next != NULL)
			newnode = newnode -> next;
		newnode -> next = new;
	}
}
