/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:53:11 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/30 19:53:50 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "builtins.h"
# include "structs.h"
# include <termios.h>
# include <signal.h>
# include <errno.h>

extern int	g_signal_status;

///////// input validation /////////

int				in_redir(t_data *shell, char *input);
int				in_pipes(t_data *shell, char *input);
bool			empty_line(char *line);

bool			check_space(char ch);
char			*change_to_space(char *line);
void			change_space_to_31(char *p_token);

bool			has_unclosed_quotes(char *line);
int				skip_quotes(char *line, int i);
void			remove_quotes(char *str);
int				skip_quotes(char *line, int i);
int				quotes_redir(char *line);
int				q_pipe(t_data *shell, char *line);
int				is_in_quotes(char c, int *in_single_quote,
					int *in_double_quote);
void			error_message(t_data *shell, char *msg, int status);
void			msg_status(t_data *shell, char *msg, int status);
void			init_t_data(t_data *data);
void			init_t_data2(t_data *data, t_pipex *pipex);
void			init_cmd(t_cmd *cmd);

////////////// parsing ///////////////

char			**do_split(char const *s, char c);
void			split_line(char *line, t_data *shell);
void			*is_heredoc(char *line, t_data *tokens);
char			*hd_filename(t_data *shell, int count);
int				process_hd(t_data *tokens, const char *file,
					char *delimeter);
char			*expand_var(t_data *shell, char *line);
char			*get_expand(t_data *shell, char *line);
void			cmd_and_expand(t_data *shell);
int				end_character(char c);
char			*receive_exit_status(t_data *shell);
void			make_redirs(t_data *tokens);
void			remove_redir_from_input(t_data *tokens);

//////// utils functions /////////////////

char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strndup(const char *str, size_t n);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strcpy(char *dest, const char *src);

//////////////exit and free//////////////

void			get_signal(t_signal mode);
void			exit_free(t_data *shell, int status);
void			free_all_sh(t_data *shell);
void			f_free_cmds(t_cmd *cmds, int cmds_count);
void			free_t_data(t_data *shell);
void			ft_exit(t_data *shell, char **args);
void			f_free_array(char **r);
unsigned int	num_of_str(const char *s, char c);

void			restore_stdin(t_data *shell);
void			copy_fd_with_redir(t_data *shell);
void			redir_no_built(t_data *shell, t_pipex *pipex, int i);
void			no_redir_no_built(t_data *shell, t_pipex *pipex);
void			redir_builtin(t_data *shell, t_pipex *pipex, int i);

#endif
