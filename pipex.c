/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:47:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/28 15:50:22 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	free_for_path(t_data *shell, t_pipex *pipex)
{
	shell->exit_status = 1;
	free_fun(pipex);
}

void	if_not_current(char **current_path, t_data *shell, char *child)
{
	if (!current_path)
	{
		ft_putstr_fd(child, 2);
		ft_putstr_fd("!: command not found\n", 2);
		shell->exit_status = 127;
	}
}

char	*path_commands(t_data *shell, t_pipex *pipex, char **child)
{
	char	**current_path;

	current_path = pipex->commands_path;
	while (*current_path)
	{
		shell->command_temp = ft_strjoin(*current_path, "/");
		if (!shell->command_temp)
		{
			free_for_path(shell, pipex);
			return (NULL);
		}
		shell->command = ft_strjoin(shell->command_temp, *child);
		free(shell->command_temp);
		if (!shell->command)
		{
			free_for_path(shell, pipex);
			return (NULL);
		}
		if (access(shell->command, F_OK | X_OK) == 0)
			return (shell->command);
		free(shell->command);
		current_path++;
	}
	if_not_current(current_path, shell, *child);
	return (NULL);
}

char	*mine_path(t_data *shell, int i)
{
	char	**envp_copy;

	envp_copy = shell->envp;
	if (envp_copy == NULL)
	{
		ft_putstr_fd("Environment variables not found.\n", 2);
		return (NULL);
	}
	while (*envp_copy != NULL && ft_strncmp("PATH=", *envp_copy, 5) != 0)
		envp_copy++;
	if (*envp_copy == NULL)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(shell->cmds[i].word_tok[0], 2);
		ft_putstr_fd(": No such file or directory \n", 2);
		shell->exit_status = 127;
		return (NULL);
	}
	return (*envp_copy + 5);
}
