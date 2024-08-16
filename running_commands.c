/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:32:15 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/30 20:00:21 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stdin(t_data *shell)
{
	if (dup2(shell->temp_stdin, STDIN_FILENO) < 0)
	{
		perror("restore_stdin: dup2");
		exit(1);
	}
	close(shell->temp_stdin);
	if (dup2(shell->temp_stdout, STDOUT_FILENO) < 0)
	{
		perror("restore_stdout: dup2");
		exit(1);
	}
	close(shell->temp_stdout);
}

void	copy_fd_with_redir(t_data *shell)
{
	shell->temp_stdin = dup(STDIN_FILENO);
	if (shell->temp_stdin < 0)
	{
		perror("running_commands: dup");
		exit(1);
	}
	shell->temp_stdout = dup(STDOUT_FILENO);
	if (shell->temp_stdout < 0)
	{
		perror("running_commands: dup");
		exit(1);
	}
}

void	redir_builtin(t_data *shell, t_pipex *pipex, int i)
{
	if (if_it_is_builtins(&shell->cmds[0]) == 1)
	{
		if (shell->cmds[0].number_of_redir == 0)
			builtins(shell, &shell->cmds[0], 0);
		if (shell->cmds[0].number_of_redir > 0)
		{
			while (shell->cmds[0].number_of_redir > 0)
			{
				redirection_with_builtins(shell, pipex, i);
				shell->cmds[0].number_of_redir--;
				i++;
			}
		}
	}
}

void	redir_no_built(t_data *shell, t_pipex *pipex, int i)
{
	int	executed;

	executed = 0;
	if (shell->cmds[0].number_of_redir > 0 && \
			if_it_is_builtins(&shell->cmds[0]) == 0)
	{
		while (shell->cmds->filetype[i])
		{
			if (shell->cmds->word_tok[0] == NULL)
			{
				copy_fd_with_redir(shell);
				check_filetype(shell, pipex, shell->cmds);
				restore_stdin(shell);
			}
			if (shell->cmds->word_tok[0] != NULL && !executed)
			{
				forking(shell, *pipex);
				closing(shell);
				executed = 1;
			}
			i++;
		}
	}
}

void	no_redir_no_built(t_data *shell, t_pipex *pipex)
{
	if (if_it_is_builtins(&shell->cmds[0]) == 0 && \
			shell->cmds[0].number_of_redir == 0)
	{
		forking(shell, *pipex);
		closing(shell);
	}
}
