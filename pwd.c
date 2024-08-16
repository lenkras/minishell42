/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:08:54 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/19 14:06:41 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "structs.h"

void	free_pwd(t_data *data, char *pwd_value)
{
	free(pwd_value);
	data->exit_status = 1;
	return ;
}

void	old_pwd_k(char *old_pwd, char *pwd_value, char *original, t_data *data)
{
	old_pwd = ft_strjoin("OLDPWD=", original);
	if (old_pwd != NULL)
	{
		if (data->envp)
		{
			free(data->envp[data->oldpwd_index]);
			data->envp[data->oldpwd_index] = NULL;
		}
		data->envp[data->oldpwd_index] = ft_strdup(old_pwd);
		if (data->envp[data->oldpwd_index] == NULL)
		{
			free(old_pwd);
			free_pwd(data, pwd_value);
		}
		free(old_pwd);
	}
	else
	{
		free(pwd_value);
		return ;
	}
	free(pwd_value);
}

void	new_pwd_k(char *new_pwd, char *pwd_value, t_data *data)
{
	new_pwd = ft_strjoin("PWD=", pwd_value);
	if (new_pwd != NULL)
	{
		if (data->envp)
		{
			free(data->envp[data->pwd_index]);
			data->envp[data->pwd_index] = NULL;
		}
		data->envp[data->pwd_index] = ft_strdup(new_pwd);
		if (data->envp[data->pwd_index] == NULL)
		{
			free(new_pwd);
			free_pwd(data, pwd_value);
		}
		free(new_pwd);
	}
	else
	{
		free(pwd_value);
		return ;
	}
}
