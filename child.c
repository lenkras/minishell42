/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:22:11 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/30 19:37:41 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	dup_close(int k, t_data *shell)
{
	int	i;

	i = 0;
	if (shell->pipe)
	{
		if (k != 0)
			dup2(shell->pipe[k - 1][0], STDIN_FILENO);
		if (k != shell->cmds_count - 1)
			dup2(shell->pipe[k][1], STDOUT_FILENO);
		while (i < (shell->pipe_count))
		{
			close(shell->pipe[i][0]);
			close(shell->pipe[i][1]);
			i++;
		}
	}
}

int	find_slash(t_cmd *cmd)
{
	if (strchr(cmd->word_tok[0], '/') != NULL)
		return (1);
	return (0);
}

void	exeve_for_commands(t_data *shell, t_pipex pipex, int k)
{
	char	*final;

	final = NULL;
	if (shell->cmds->word_tok[0] != NULL && find_slash(&shell->cmds[k]) == 1)
		final = shell->cmds[k].word_tok[0];
	else
	{
		checking_path(shell, &pipex, k);
		final = path_commands(shell, &pipex, &shell->cmds[k].word_tok[0]);
	}
	if (!final)
	{
		printf("%s: command not found\n", shell->cmds[k].word_tok[0]);
		exit(127);
	}
	if (execve(final, shell->cmds[k].word_tok, shell->envp) == -1)
	{
		if (shell->envp)
		{
			free_array(shell->envp);
			shell->envp = NULL;
		}
		printf("sashel: %s: Not a directory \n", shell->cmds[k].word_tok[0]);
		free_fun(&pipex);
	}
}

void	child(t_pipex pipex, t_data *shell, int k)
{
	int		i;

	i = 0;
	dup_close(k, shell);
	check_filetype(shell, &pipex, &shell->cmds[k]);
	if (if_it_is_builtins(&shell->cmds[k]) == 1)
	{
		builtins(shell, &shell->cmds[k], k);
		exit(0);
	}
	else
		exeve_for_commands(shell, pipex, k);
}
