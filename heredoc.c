/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:05:10 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/29 14:55:58 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hd_filename(t_data *shell, int count)
{
	char	*temp;

	temp = ft_itoa(count);
	if (!temp)
		error_message(shell, "Failed to create file for heredoc", 1);
	shell->file = ft_strjoin(".heredoc", temp);
	free (temp);
	if (!shell->file)
	{
		free(shell->file);
		free_all_sh(shell);
		error_message(shell, "Failed to create file for heredoc", 1);
	}
	return (shell->file);
}

static char	*extract_delimiter(char *line, int *i)
{
	int		start;
	int		len;
	char	*delimiter;

	len = 0;
	while (check_space(line[*i]))
		(*i)++;
	start = *i;
	while (line[*i] && line[*i] != 31 && !check_space(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			remove_quotes(&line[*i]);
		len++;
		(*i)++;
	}
	delimiter = (char *)malloc(sizeof(char) * (len + 1));
	if (!delimiter)
		return (NULL);
	ft_strncpy(delimiter, &line[start], len);
	delimiter[len] = '\0';
	return (delimiter);
}

void	freeing(t_data *tokens)
{
	free(tokens->hd_delimeter);
	tokens->hd_delimeter = NULL;
	free(tokens->tempfile_hd);
	tokens->tempfile_hd = NULL;
}

static int	handle_heredoc(char *line, int *i, t_data *tokens)
{
	tokens->hd_count++;
	*i += 2;
	tokens->hd_delimeter = extract_delimiter(line, i);
	if (!tokens->hd_delimeter)
	{
		error_message(tokens, "Memory allocation error\n", 1);
		return (-1);
	}
	tokens->tempfile_hd = hd_filename(tokens, tokens->hd_count);
	if (!tokens->tempfile_hd)
	{
		error_message(tokens, "Failed to assign filename for heredoc", 1);
		free(tokens->tempfile_hd);
		tokens->tempfile_hd = NULL;
		return (-1);
	}
	if (process_hd(tokens, tokens->tempfile_hd, tokens->hd_delimeter) == -1)
	{
		freeing(tokens);
		return (-1);
	}
	freeing(tokens);
	return (0);
}

void	*is_heredoc(char *line, t_data *tokens)
{
	int		i;
	int		in_quote;

	i = 0;
	in_quote = 0;
	tokens->hd_count = 0;
	g_signal_status = 0;
	while (line[i] && !g_signal_status)
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			in_quote = !in_quote;
			i++;
			continue ;
		}
		if ((ft_strncmp(&line[i], "<<", 2) == 0) && !in_quote)
		{
			if (handle_heredoc(line, &i, tokens) == -1)
				break ;
		}
		if (line[i] != '\0')
			i++;
	}
	return (0);
}
