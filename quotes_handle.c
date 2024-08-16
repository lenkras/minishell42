/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-26 10:45:47 by epolkhov          #+#    #+#             */
/*   Updated: 2024-06-26 10:45:47 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	skip_quotes(char *line, int i)
{
	char	quote;

	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	return (i);
}

bool	has_unclosed_quotes(char *line)
{
	int		i;
	bool	single_quote_open;
	bool	double_quote_open;

	single_quote_open = false;
	double_quote_open = false;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			single_quote_open = !single_quote_open;
		else if (line[i] == '\"')
			double_quote_open = !double_quote_open;
		i++;
	}
	return (single_quote_open || double_quote_open);
}

void	remove_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

int	q_pipe(t_data *shell, char *line)
{
	int	i;
	int	in_sq;
	int	in_dq;

	i = 0;
	in_sq = 0;
	in_dq = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			in_dq = !in_dq;
		else if (line[i] == '\'')
			in_sq = !in_sq;
		if (line[i] == '|' && !in_sq && !in_dq)
			line[i] = 31;
		i++;
	}
	if (has_unclosed_quotes(line))
	{
		ft_putendl_fd("Syntax error: unclosed quotes", 2);
		shell->exit_status = 2;
		return (1);
	}
	return (0);
}

int	is_in_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (c == '\"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
	return (*in_single_quote || *in_double_quote);
}
