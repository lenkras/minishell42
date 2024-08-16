/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:12:53 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/18 19:48:00 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_and_redir(t_data *shell)
{
	make_redirs(shell);
	remove_redir_from_input(shell);
}

static t_cmd	split_into_wtok(char *pipe_token, t_cmd cmd)
{
	change_space_to_31(pipe_token);
	remove_quotes(pipe_token);
	cmd.word_tok = do_split(pipe_token, 31);
	if (!cmd.word_tok)
	{
		return (cmd);
	}
	while (cmd.word_tok[cmd.w_count])
		cmd.w_count++;
	return (cmd);
}

static void	count_commands(t_data *shell)
{
	shell->cmds_count = 0;
	while (shell->pipe_tok[shell->cmds_count])
		shell->cmds_count++;
}

static void	process_commands(t_data *shell)
{
	int	i;

	i = -1;
	while (++i < shell->cmds_count)
	{
		shell->cmds[i] = split_into_wtok(shell->pipe_tok[i], shell->cmds[i]);
		if (!shell->cmds[i].word_tok)
		{
			error_message(shell, "Failed to split to tokens", 1);
			return ;
		}
	}
}

void	split_line(char *line, t_data *shell)
{
	int		i;

	shell->cmds_count = 0;
	if (quotes_redir(line) == 0)
		is_heredoc(line, shell);
	shell->pipe_tok = do_split(line, 31);
	if (!shell->pipe_tok)
	{
		error_message(shell, "Failed to malloc", 1);
		return ;
	}
	count_commands(shell);
	shell->cmds = (t_cmd *)malloc(sizeof(t_cmd) * shell->cmds_count);
	if (!shell->cmds)
		error_message(shell, "Failed to allocate memory", 1);
	i = -1;
	while (++i < shell->cmds_count)
		init_cmd(&shell->cmds[i]);
	if (quotes_redir(shell->pipe_tok[0]) == 0)
	{
		cmd_and_redir(shell);
		cmd_and_expand(shell);
	}
	process_commands(shell);
}
