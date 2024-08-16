/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:45:33 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/15 17:00:02 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

void	new_envp_size(t_data *data, int new, int i, char **new_envp)
{
	while (new < i)
	{
		new_envp[new] = data->envp[new];
		new++;
	}
}

void	input_checker(t_data *shell, char *input_copy)
{
	if_error_input(shell, input_copy);
	if_quotes(input_copy);
}

void	checking_export(t_data *data)
{
	int		i;
	char	*kuku;

	i = 0;
	while (data->envp[i] != NULL)
	{
		if (data->envp[i][0] != '_')
		{
			kuku = ft_strchr(data->envp[i], '=');
			if (kuku != NULL)
				printf("declare -x %.*s=\"%s\"\n", (int)(kuku - data->envp[i]), \
					data->envp[i], kuku + 1);
			else
				printf("declare -x %s\n", data->envp[i]);
			i++;
		}
		else
			i++;
	}
}

int	is_var_in_envp(char *arg, t_data *data)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strchr(arg, '=') - arg;
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], arg, len) == 0)
			return (i);
		else if (ft_strncmp(data->envp[i], arg, len) == 0 && \
			data->envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	if_error_input(t_data *shell, char *input_copy)
{
	if (input_copy == NULL)
	{
		perror("malloc");
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
}
