/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:54:57 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/26 12:59:28 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

//prototyping prompt struct
typedef struct s_shell	t_shell;

//execution_util.c
bool	input_redir_check(t_exec *exec);
bool	pipe_check(t_exec *exec);
bool	is_valid_id(char *token);
void	redir_output(t_shell *shell, t_exec *exec);

//execution.c
int		find_builtin(t_shell *shell, t_exec *exec);
void	single_exe(t_shell *shell, t_exec *exec);
void	exec_cmd(t_shell *shell, t_exec *exec);
void	execution(t_shell *shell);
int		single_exec(t_shell *shell, t_exec *exec);

//find_path_1.c
void	exit_path(t_shell *shell, char **paths, char *cmd, int exit_status_x);
char	**get_paths(t_shell *shell);
char	*get_bin_path(char *cmd, char **paths);
void	err_cmd(char *cmd);
char	**append_cmd_front(t_shell *shell, char **args);

//find_path_2.c
int		ft_exec_external(t_shell *shell, char *cmd, char **path);
int		find_path(t_shell *shell, t_exec *exec);
void	terminate_bin_path(t_shell *shell, char *cmd, char **paths);
void	terminate_bin_path_2(t_shell *shell, char *cmd, char **paths);
t_exec	*return_exec(t_shell *shell, t_exec *exec);

//pipe.c
void	left_side(t_exec *exec, t_shell *shell, int pipe_fd[2]);
void	right_side(t_exec *exec, t_shell *shell, int pipe_fd[2]);
void	pipe_exe(t_shell *shell, t_exec *exec);

//redir_1.c
void	remove_less(t_shell *shell, t_exec *exec);
void	less(t_shell *shell, t_exec *exec);
void	heredoc(t_shell *shell, t_exec *exec);
void	ft_open(char *token, int option);
void	remove_output_node(t_shell *shell, t_exec *exec);

//redir_2.c
char	**add_string(char **array, int *size, const char *new_string);
char	**add_string_util(char **n_arr, char **arr, int *s, const char *n_str);
t_exec	*cat_exec(t_exec *exec);
void	redir_exe(t_shell *shell, t_exec *exec);
int		is_directory(char *path);

#endif
