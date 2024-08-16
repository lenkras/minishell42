/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:29:45 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/19 14:06:23 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "structs.h"

void	cd_without_arg(t_data *data, char *original)
{
	int	home;
	int	found_home;

	home = 0;
	found_home = 0;
	while (data->envp[home] != NULL)
	{
		if (ft_strncmp(data->envp[home], "HOME=", 5) == 0)
		{
			found_home = 1;
			break ;
		}
		home++;
	}
	checking_home(found_home, data, home, original);
}

void	cd_with_one_arg(t_data *shell, char *original)
{
	if (chdir(shell->cmds->word_tok[1]) == 0)
	{
		search_old_current(shell);
		update_pwd(shell, original);
	}
	else if (chdir(shell->cmds->word_tok[1]) != 0)
	{
		printf("bash: cd: %s No such file or directory\n", \
			shell->cmds->word_tok[1]);
		shell->exit_status = 1;
	}
}

void	ft_cd(t_data *data, int number_of_inputs)
{
	char	*original;

	data->pwd_index = 0;
	data->oldpwd_index = 0;
	original = getcwd(data->pwd, sizeof(data->pwd));
	if (number_of_inputs < 2)
		cd_without_arg(data, original);
	else if (number_of_inputs == 2)
		cd_with_one_arg(data, original);
	else if (number_of_inputs > 2)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 1);
		data->exit_status = 1;
	}
}
