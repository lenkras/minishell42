/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:35:40 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/30 19:49:47 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

void	if_added_var(char *added_var, char **new_envp, t_data *data)
{
	if (added_var != NULL)
	{
		new_envp[data->envp_size] = added_var;
		new_envp[data->envp_size + 1] = NULL;
		free(data->envp);
		data->envp = new_envp;
	}
	else if (!added_var)
	{
		free(new_envp);
		data->exit_status = 1;
		perror("ft_strdup");
	}
}

void	not_in_var(t_data *data, char *input_copy, char *added_var)
{
	char	**new_envp;
	int		new;

	new = 0;
	while (data->envp[data->envp_size] != NULL)
		data->envp_size++;
	new_envp = malloc((data->envp_size + 2) * sizeof(char *));
	if (new_envp == NULL)
	{
		perror("malloc");
		data->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	new_envp_size(data, new, data->envp_size, new_envp);
	added_var = ft_strdup(input_copy);
	if_added_var(added_var, new_envp, data);
}

void	found_var(t_data *shell, int index, char *added_var, char *input_copy)
{
	free(shell->envp[index]);
	added_var = ft_strdup(input_copy);
	if (added_var != NULL)
		shell->envp[index] = added_var;
	else if (!added_var)
	{
		perror("ft_strdup");
		shell->exit_status = 1;
		free(input_copy);
		return ;
	}
}

void	export_with(t_data *shell, int number_of_inputs)
{
	char	*added_var;
	char	*input_copy;
	int		j;
	int		var_index;

	added_var = NULL;
	j = 1;
	while (j < number_of_inputs)
	{
		input_copy = ft_strdup(shell->cmds->word_tok[j]);
		if (input_copy == NULL)
		{
			perror("ft_strdup");
			shell->exit_status = 1;
			return ;
		}
		input_checker(shell, input_copy);
		var_index = is_var_in_envp(input_copy, shell);
		if (var_index >= 0)
			found_var(shell, var_index, added_var, input_copy);
		else
			not_in_var(shell, input_copy, added_var);
		free(input_copy);
		j++;
	}
}

void	ft_export(t_data *data, int number_of_inputs)
{
	if (number_of_inputs > 1)
		export_with(data, number_of_inputs);
	else if (number_of_inputs == 1)
		checking_export(data);
}
