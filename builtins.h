/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:32:50 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/28 15:49:01 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "minishell.h"
# include "structs.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_words(const char *str, char c);
char	*ft_wd(const char *str, char c);
void	free_w(size_t i, char **ptr);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strpbrk(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str );
char	*ft_strdup(const char *src);
void	unset_var(t_data *data, char *arg);
void	ft_echo(t_data *data, int number_of_inputs, int k);
void	ft_export(t_data *data, int number_of_inputs);
void	ft_env(t_data *data);
void	ft_unset(t_data *data, int number_of_inputs);
void	ft_cd(t_data *data, int number_of_inputs);
void	ft_pwd(t_data *shell);
int		is_var_in_envp(char *arg, t_data *data);
void	if_quotes(char *str);
void	cd_without_arg(t_data *data, char *original);
void	cd_with_one_arg(t_data *data, char *original);
void	update_pwd(t_data *data, char *original);
void	search_old_current(t_data *data);
void	checking_export(t_data *data);
void	not_in_var(t_data *data, char *input_copy, char *added_var);
void	export_with(t_data *data, int number_of_inputs);
void	if_error_input(t_data *shell, char *input_copy);
char	*mine_path(t_data *shell, int i);
void	free_fun(t_pipex *pipex);
int		open_fd_in(t_data *shell, t_pipex *pipex,
			int filetype, char *filenames);
void	open_fd_out(t_data *shell, t_pipex *pipex,
			int filetype, char *filename);
void	free_array(char **array);
void	ft_error(void);
char	*path_commands(t_data *shell, t_pipex *pipex, char **child_command);
void	builtins(t_data *data, t_cmd *cmd, int k);
int		if_it_is_builtins( t_cmd *cmd);
void	child(t_pipex pipex, t_data *shell, int k);
void	check_filetype(t_data *shell, t_pipex *pipex, t_cmd *cmd);
void	checking_path(t_data *shell, t_pipex *pipex, int i);
void	piping(t_data *shell);
void	forking(t_data *shell, t_pipex pipex);
void	closing(t_data *shell);
void	redirection_out_builtin(t_data *shell, t_pipex *pipex, int i);
void	redirection_in_builtin(t_data *shell, t_pipex *pipex, int i);
void	redirection_with_builtins(t_data *shell, t_pipex *pipex, int i);
void	checking_home(int found_home, t_data *data, int home, char *original);
void	running_commands(t_data *shell, int i, t_pipex *pipex );
void	old_pwd_k(char *old_pwd, char *pwd_value, char *original, t_data *data);
void	new_pwd_k(char *new_pwd, char *pwd_value, t_data *data);
void	dup_close(int k, t_data *shell);
void	found_var(t_data *shell, int var_index,
			char *added_var, char *input_copy);
void	input_checker(t_data *shell, char *input_copy);
void	if_added_var(char *added_var, char **new_envp, t_data *data);
void	new_envp_size(t_data *data, int new, int i, char **new_envp);
void	msg_status(t_data *shell, char *msg, int status);
void	exeve_for_commands(t_data *shell, t_pipex pipex, int k);
void	open_fd_out_app(t_data *shell, t_pipex *pipex,
			int filetype, char *filename);
void	free_for_path(t_data *shell, t_pipex *pipex);
char	*ft_getenv(t_data *shell, char *env);
char	*expand_var(t_data *shell, char *line);
void	creating_filename(int j, char *line, int i, t_data *sh);
void	removing( t_data *sh, int j, int k, int i);
void	updating_variables(t_data *sh, int j, int k, int i);
void	if_exist_filename(t_data *sh, int i);
void	updating_filenames(t_data *sh, int i, char *line);
void	freeing_after_closing(t_data *shell);
void	error_message(t_data *shell, char *msg, int status);
void	if_not_current(char **current_path, t_data *shell, char *child);
#endif