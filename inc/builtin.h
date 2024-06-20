/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:00:52 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/20 16:41:55 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

//prototyping prompt struct
typedef struct s_shell	t_shell;

//cd.c
int		builtin_cd(t_shell *shell, t_exec *exec);
int	cd_home(t_shell *shell);
void	set_last_dir(t_shell *shell);
void	change_last_dir(t_shell *shell);

//echo.c
int	builtin_echo(t_exec *exec);
int		check_echo_option(char **args, int **n_flag, int i);
int		find_if_n(char *str);

//env.c
int	builtin_env(t_shell *shell, t_exec *exec);

//exit.c
void	builtin_exit(t_shell *shell, t_exec *exec);
int 	ft_isnum(char *str);
int get_exit(int exit_code);

//export.c
int	builtin_export(t_shell *shell, t_exec *exec);
int	update_env_declare(t_shell *shell, t_exec *exec);
int		valid_format(char *str);
void	add_declare(t_shell *shell, char *str, int var);
void	add_env(t_shell *shell, char *str);

//pwd.c
int	builtin_pwd(t_shell *shell);
void	update_pwd_env_declare(t_shell *shell, char *str);

//unset.c
int		builtin_unset(t_shell *shell, t_exec *exec);
void	unset_declare(t_shell *shell, char *str);
void	unset_env(t_shell *shell, char *str);

#endif
