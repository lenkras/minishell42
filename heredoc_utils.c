/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-18 09:17:33 by epolkhov          #+#    #+#             */
/*   Updated: 2024-07-18 09:17:33 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_line(char *line, t_data *tokens, char *delimiter, int fd)
{
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	if (ft_strchr(line, '$'))
		line = expand_var(tokens, line);
	ft_putendl_fd(line, fd);
	free(line);
	return (0);
}

static int	handle_error(int stdin)
{
	if (errno && errno == EBADF)
	{
		dup2(stdin, STDIN_FILENO);
		close(stdin);
		return (-1);
	}
	return (0);
}

static int	hd_readline(char *line, t_data *tokens, char *delimeter, int fd)
{
	int	stdin;

	errno = 0;
	stdin = dup(STDIN_FILENO);
	if (stdin == -1)
		return (-1);
	while (1)
	{		
		if (g_signal_status)
		{
			free(line);
			dup2(stdin, STDIN_FILENO);
			close(stdin);
			return (-1);
		}
		line = readline("> ");
		if (!line)
			break ;
		if (process_line(line, tokens, delimeter, fd))
			break ;
	}
	return (handle_error(stdin));
}

int	process_hd(t_data *tokens, const char *file, char *delimeter)
{
	int		fd;
	char	*line;

	line = NULL;
	get_signal(HEREDOC);
	unlink(file);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_message(tokens, "Failed to open fd for heredoc", 1);
	if (hd_readline(line, tokens, delimeter, fd) == -1)
	{
		close (fd);
		unlink(file);
		get_signal(HANDLER);
		return (-1);
	}
	if (close(fd) == -1)
		error_message(tokens, "Failed to close fd for heredoc", 1);
	get_signal(HANDLER);
	return (0);
}
