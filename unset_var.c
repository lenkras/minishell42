/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:56:28 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/28 14:31:45 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	unset_var(t_data *data, char *arg)
{
	int	i;
	int	j;

	data->len = ft_strlen(arg);
	i = 0;
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], arg, data->len) == 0 && \
			data->envp[i][data->len] == '=')
			break ;
		i++;
	}
	if (data->envp[i] == NULL)
	{
		printf("Environment variable %s not found.\n", arg);
		return ;
	}
	free(data->envp[i]);
	j = i;
	while (data->envp[j + 1] != NULL)
	{
		data->envp[j] = data->envp[j + 1];
		j++;
	}
	data->envp[j] = NULL;
}
