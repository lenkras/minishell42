/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:17:10 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/28 15:18:13 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	error_message(t_data *shell, char *msg, int status)
{
	if (shell)
		free_all_sh(shell);
	perror(msg);
	shell->exit_status = status;
	exit (status);
}
