/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:34:09 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/19 11:51:26 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	if_it_is_builtins( t_cmd *cmd)
{
	if (cmd->word_tok[0] != NULL)
	{
		if (ft_strncmp(cmd->word_tok[0], "pwd", 4) == 0)
			return (1);
		else if (ft_strncmp(cmd->word_tok[0], "echo", 5) == 0)
			return (1);
		else if (ft_strncmp(cmd->word_tok[0], "env", 4) == 0)
			return (1);
		else if (ft_strncmp(cmd->word_tok[0], "export", 7) == 0)
			return (1);
		else if (ft_strncmp(cmd->word_tok[0], "cd", 3) == 0)
			return (1);
		else if (ft_strncmp(cmd->word_tok[0], "unset", 6) == 0)
			return (1);
		else if (ft_strncmp(cmd->word_tok[0], "exit", 5) == 0)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

void	builtins(t_data *data, t_cmd *cmd, int k)
{
	if (ft_strncmp(cmd->word_tok[0], "pwd", 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp(cmd->word_tok[0], "echo", 5) == 0)
		ft_echo(data, cmd->w_count, k);
	else if (ft_strncmp(cmd->word_tok[0], "env", 4) == 0)
		ft_env(data);
	else if (ft_strncmp(cmd->word_tok[0], "export", 7) == 0)
		ft_export(data, cmd->w_count);
	else if (ft_strncmp(cmd->word_tok[0], "cd", 3) == 0)
		ft_cd(data, cmd->w_count);
	else if (ft_strncmp(cmd->word_tok[0], "unset", 6) == 0)
		ft_unset(data, cmd->w_count);
	else if (ft_strncmp(cmd->word_tok[0], "exit", 5) == 0)
		ft_exit(data, &cmd->word_tok[0]);
}
