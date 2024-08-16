/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:43:44 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/19 11:50:37 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

void	ft_pwd(t_data *shell)
{
	printf("%s\n", getcwd(shell->pwd, sizeof(shell->pwd)));
}

void	if_quotes(char *str)
{
	char	*write_ptr;
	char	quote_char;
	char	*read_ptr;

	write_ptr = str;
	read_ptr = str;
	quote_char = 0;
	while (*read_ptr)
	{
		if (*read_ptr == '\'' || *read_ptr == '\"')
		{
			if (quote_char == 0)
				quote_char = *read_ptr;
			else if (quote_char == *read_ptr)
				quote_char = 0;
			read_ptr++;
		}
		else
			*write_ptr++ = *read_ptr++;
	}
	*write_ptr = '\0';
}

void	ft_unset(t_data *shell, int number_of_inputs)
{
	int	k;

	k = 1;
	if (number_of_inputs == 1)
		ft_putstr_fd("", 1);
	if (number_of_inputs >= 2)
	{
		while (k < number_of_inputs)
			unset_var(shell, shell->cmds->word_tok[k++]);
	}
}

void	ft_echo(t_data *shell, int number_of_inputs, int k)

{
	int	flag;
	int	i;

	i = 2;
	flag = 0;
	if (number_of_inputs > 2 && \
		ft_strncmp(shell->cmds->word_tok[1], "-n", 3) == 0)
	{
		flag = 1;
		i = 3;
	}
	if (number_of_inputs <= 1)
		ft_putstr_fd("\n", 1);
	else
	{
		while (number_of_inputs >= i)
		{
			ft_putstr_fd(shell->cmds[k].word_tok[i - 1], 1);
			if (number_of_inputs > i)
				ft_putstr_fd(" ", 1);
			i++;
		}
		if (!flag)
			ft_putstr_fd("\n", 1);
	}
}

void	ft_env(t_data *data)
{	
	int		i;
	char	*kuku;

	i = 0;
	while (data->envp[i] != NULL)
	{
		kuku = ft_strchr(data->envp[i], '=');
		if (kuku != NULL)
		{
			printf("%s\n", data->envp[i]);
			i++;
		}
		else
			i++;
	}
}
