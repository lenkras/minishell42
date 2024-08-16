/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:44:41 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/19 11:28:14 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	remove_redir_from_input(t_data *sh)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	while (sh->pipe_tok[++i] && i < sh->cmds_count)
		removing(sh, j, k, i);
}

void	make_redirs(t_data *sh)
{
	int			i;
	int			j;
	char		*line;

	line = NULL;
	j = 0;
	i = -1;
	sh->hd_index = 1;
	while (sh->pipe_tok[++i] && i < sh->cmds_count)
	{
		creating_filename(j, line, i, sh);
		sh->cmds[i].filenames[sh->redir_count] = NULL;
		sh->cmds[i].filetype[sh->redir_count] = NONE;
		sh->cmds[i].number_of_redir = sh->redir_count;
	}
}

void	if_exist_filename(t_data *sh, int i)
{
	if (sh->cmds[i].type == HERE)
	{
		sh->cmds[i].filenames[sh->redir_count] = hd_filename(sh,
				sh->hd_index++);
		free(sh->filename);
		sh->filename = NULL;
	}
	else
		sh->cmds[i].filenames[sh->redir_count] = sh->filename;
	sh->cmds[i].filetype[sh->redir_count] = sh->cmds[i].type;
	sh->redir_count++;
}

void	updating_filenames(t_data *sh, int i, char *line)
{
	sh->cmds[i].filenames = malloc(sizeof(char *) * (ft_strlen(line) + 1));
	sh->cmds[i].filetype = malloc(sizeof(int) * (ft_strlen(line) + 1));
	if (!sh->cmds[i].filenames || !sh->cmds[i].filetype)
		error_message(sh, "Memory allocation error", 1);
}
