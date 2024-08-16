/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:18:08 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/28 15:28:24 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	msg_status(t_data *shell, char *msg, int status)
{
	ft_putendl_fd(msg, 2);
	shell->exit_status = status;
}

int	in_pipes(t_data *shell, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			{
				msg_status(shell, "Syntax error: multiple pipes", 2);
				return (1);
			}
			i++;
			while (check_space(input[i]))
				i++;
			if (input[i] == '|' || input[i] == '\0')
			{
				msg_status(shell, \
				"Syntax error: no input after unexpected token", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	is_redirection(char c, char next_c)
{
	return (c == '<' || c == '>' || \
			(c == '>' && next_c == '>') || (c == '<' && next_c == '<'));
}

static int	validate_redirection(t_data *shell, char *in, int i, \
				int in_double_quote)
{
	if ((in[i] == '|' || in[i] == '\0' || in[i] == '<' || in[i] == '>') && \
			!shell->in_single_quote && !in_double_quote)
	{
		msg_status(shell, "Syntax error: no input after unexpected token", 2);
		return (1);
	}
	return (0);
}

int	in_redir(t_data *shell, char *in)
{
	int	i;
	int	in_double_quote;

	i = 0;
	shell->in_single_quote = 0;
	in_double_quote = 0;
	while (in[i])
	{
		is_in_quotes(in[i], &shell->in_single_quote, &in_double_quote);
		if (is_redirection(in[i], in[i + 1]) && \
			!(shell->in_single_quote || in_double_quote))
		{
			if (in[i + 1] == '>' || in[i + 1] == '<')
				i += 2;
			else
				i++;
			while (check_space(in[i]))
				i++;
			if (validate_redirection(shell, in, i, in_double_quote))
				return (1);
		}
		else
			i++;
	}
	return (0);
}

// static int	validate_redirection(t_data *shell,
// char *in, int i, 
// 	int in_single_quote, int in_double_quote)
// {
// 	if ((in[i] == '|' || in[i] == '\0' || 
//in[i] == '<' || in[i] == '>') && 
// 			!in_single_quote && !in_double_quote)
// 	{
// 		msg_status(shell, "Syntax error: no input after unexpected token", 2);
// 		return (1);
// 	}
// 	return (0);
// }

// int	in_redir(t_data *shell, char *in)
// {
// 	int	i;
// 	int	in_single_quote;
// 	int	in_double_quote;

// 	i = 0;
// 	in_single_quote = 0;
// 	in_double_quote = 0;
// 	while (in[i])
// 	{
// 		is_in_quotes(in[i], &in_single_quote,
// &in_double_quote);
// 		if (is_redirection(in[i],
// in[i + 1]) && 
// 			!(in_single_quote || in_double_quote))
// 		{
// 			if (in[i + 1] == '>' || in[i + 1] == '<')
// 				i += 2;
// 			else
// 				i++;
// 			while (check_space(in[i]))
// 				i++;
// 			if (validate_redirection(shell, in, i, in_single_quote,
// 								in_double_quote))
// 				return (1);
// 		}
// 		else
// 			i++;
// 	}
// 	return (0);
// }