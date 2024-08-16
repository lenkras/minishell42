/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:39:27 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/30 19:49:24 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "structs.h"

void	update_pwd(t_data *data, char *original)
{
	char	*pwd_value;
	char	*old_pwd;

	old_pwd = NULL;
	if (data->envp[data->pwd_index] != NULL)
	{
		pwd_value = getcwd(NULL, 0);
		if (pwd_value != NULL)
		{
			new_pwd_k(old_pwd, pwd_value, data);
			old_pwd_k(old_pwd, pwd_value, original, data);
		}
	}
}

void	search_old_current(t_data *data)
{
	while (data->envp[data->pwd_index++] != NULL)
	{
		if (ft_strncmp(data->envp[data->pwd_index], "PWD=", 4) == 0)
			break ;
	}
	while (data->envp[data->oldpwd_index++] != NULL)
	{
		if (ft_strncmp(data->envp[data->oldpwd_index], "OLDPWD=", 7) == 0)
			break ;
	}
}

void	checking_home(int found_home, t_data *data, int home, char *original)
{
	if (found_home)
	{
		if (chdir(data->envp[home] + 5) == 0)
		{
			search_old_current(data);
			update_pwd(data, original);
		}
	}
	else
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 1);
		data->exit_status = 1;
	}
}
