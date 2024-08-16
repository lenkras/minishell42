/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:51:19 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/15 15:24:57 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_msg(t_data *shell, char *str)
{
	char	*err_msg;
	char	*temp;

	temp = ft_strjoin("exit: ", str);
	if (!temp)
	{
		perror("Malloc failed");
		exit_free(shell, 1);
	}
	err_msg = ft_strjoin(temp, ": numeric argument required\n");
	free (temp);
	if (!err_msg)
	{
		perror ("Malloc failed");
		exit_free (shell, 1);
	}
	write (2, err_msg, ft_strlen(err_msg));
	free(err_msg);
	exit_free(shell, 255);
}

static int	if_non_digit(t_data *shell, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			error_msg(shell, str);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	convert_to_int(t_data *shell, char *str)
{
	int	n;

	if (!ft_strcmp(str, "9223372036854775807"))
		return (255);
	if (!ft_strcmp (str, "-9223372036854775808"))
		return (0);
	n = ft_atoi(str);
	if ((n == 0 && ft_strcmp(str, "0")) || (n == -1 && ft_strcmp(str, "-1")))
		error_msg(shell, str);
	return (n);
}

void	ft_exit(t_data *shell, char **args)
{
	if (isatty(STDIN_FILENO))
		printf ("exit\n");
	if (args[1])
	{
		if (if_non_digit(shell, args[1]))
			shell->exit_status = 2;
		else
			shell->exit_status = convert_to_int(shell, args[1]);
		if (shell->cmds->word_tok[2])
		{
			printf ("exit: too many arguments\n");
			shell->exit_status = 1;
			return ;
		}
	}
	else
		shell->exit_status = WEXITSTATUS(shell->exit_status);
	exit_free(shell, shell->exit_status);
}
