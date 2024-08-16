/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:46:00 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/30 19:38:06 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	free_fun(t_pipex *pipex)
{
	(void)pipex;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(126);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free (array);
}

void	f_free_array(char **str)
{
	char	**ptr;

	if (!str)
		return ;
	ptr = str;
	while (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		ptr++;
	}
	free(str);
	str = NULL;
}

void	ft_error(void)
{
	perror("Error fork()");
	exit(1);
}

void	f_free_cmds(t_cmd *cmds, int cmds_count)
{
	int		i;

	i = 0;
	while (i < cmds_count)
	{
		if (cmds[i].word_tok != NULL)
		{
			free_array(cmds[i].word_tok);
			cmds[i].word_tok = NULL;
		}
		if (cmds[i].filetype != NULL)
		{
			free(cmds[i].filetype);
			cmds[i].filetype = NULL;
		}
		if (cmds[i].filenames != NULL)
		{
			free_array(cmds[i].filenames);
			cmds[i].filenames = NULL;
		}
		i++;
	}
	free(cmds);
	cmds = NULL;
}
