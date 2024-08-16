/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:49:10 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/18 18:26:10 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static t_filetype	peek(char *line, int index)
{
	if (line[index] == '<' && line[index + 1] == '<')
		return (HERE);
	if (line[index] == '<')
		return (IN);
	if (line[index] == '>' && line[index + 1] == '>')
		return (APPEND);
	if (line[index] == '>')
		return (OUT);
	return (NONE);
}

static char	*take_filename( char *line, int *index)
{
	int		start;
	char	*filename;

	while (check_space(line[*index]))
		(*index)++;
	start = *index;
	while (line[*index] && !check_space(line[*index]) && line[*index] != '<' && \
			line[*index] != '>' && line[*index] != 31)
		(*index)++;
	filename = ft_strndup(&line[start], *index - start);
	return (filename);
}

void	creating_filename(int j, char *line, int i, t_data *sh)
{
	j = 0;
	sh->redir_count = 0;
	line = sh->pipe_tok[i];
	updating_filenames(sh, i, line);
	while (line[j])
	{
		sh->cmds[i].type = peek(line, j);
		if (sh->cmds[i].type != NONE)
		{
			if (sh->cmds[i].type == HERE || sh->cmds[i].type == APPEND)
				j += 2;
			else
				j++;
			while (check_space(line[j]))
				j++;
			sh->filename = take_filename(line, &j);
			if (sh->filename)
				if_exist_filename(sh, i);
			else
				ft_putendl_fd("Syntax error: no filename", 2);
		}
		else
			j++;
	}
}

void	updating_variables(t_data *sh, int j, int k, int i)
{
	sh->line = sh->pipe_tok[i];
	sh->new_line = (char *)malloc(sizeof(char) * (ft_strlen(sh->line) + 1));
	if (!sh->new_line)
		error_message(sh, "Failed to malloc for newline", 1);
	j = 0;
	k = 0;
}

void	removing(t_data *sh, int j, int k, int i)
{
	updating_variables(sh, j, k, i);
	while (sh->line[j])
	{
		if ((sh->line[j] == '<' || sh->line[j] == '>'))
		{
			if ((sh->line[j] == '<' && sh->line[j + 1] == '<' )
				|| (sh->line[j] == '>' && sh->line[j + 1] == '>'))
				j += 2;
			else
				j++;
			while (check_space(sh->line[j]))
				j++;
			while (sh->line[j] && sh->line[j] != '<'
				&& sh->line[j] != '>' && sh->line[j] != 31
				&& sh->line[j] != ' ')
				j++;
		}
		else
			sh->new_line[k++] = sh->line[j++];
	}
	sh->new_line[k] = '\0';
	free(sh->pipe_tok[i]);
	sh->pipe_tok[i] = sh->new_line;
}
