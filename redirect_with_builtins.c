/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_with_builtins.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:48:00 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/30 19:59:16 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	redirection_in_builtin(t_data *shell, t_pipex *pipex, int i)
{
	shell->parent_in = dup(STDIN_FILENO);
	open_fd_in(shell, pipex, shell->cmds->filetype[i], *shell->cmds->filenames);
	if (if_it_is_builtins(&shell->cmds[0]) == 1 && \
			shell->cmds[0].number_of_redir == 1 \
			&& access(*shell->cmds->filenames, F_OK) == 0)
		builtins(shell, shell->cmds, 0);
	if (dup2(shell->parent_in, STDIN_FILENO) < 0)
		printf("dup2 \n");
	close(shell->parent_in);
}

void	redirection_out_builtin(t_data *shel, t_pipex *pipex, int i)
{
	shel->parent_out = dup(STDOUT_FILENO);
	open_fd_out(shel, pipex, shel->cmds->filetype[i], *shel->cmds->filenames);
	if (if_it_is_builtins(&shel->cmds[0]) == 1 && \
			shel->cmds[0].number_of_redir == 1)
		builtins(shel, shel->cmds, 0);
	if (dup2(shel->parent_out, STDOUT_FILENO) < 0)
		printf("dup2 \n");
	close(shel->parent_out);
}

void	redirection_with_builtins(t_data *shell, t_pipex *pipex, int i)
{
	if (shell->cmds->filetype[i] == OUT)
		redirection_out_builtin(shell, pipex, i);
	if (shell->cmds->filetype[i] == IN)
		redirection_in_builtin(shell, pipex, i);
}
