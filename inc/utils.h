/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:12:05 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/25 16:52:33 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

//prototyping shell struct
typedef struct s_shell	t_shell;

//utils_1.c
char	**double_dup(char **str);
void	free_double(char **double_str);
int		ft_strlen_ms(char *s);
void	update_pwd_oldpwd(t_shell *shell, char *pwd_str, char *o_pwd_str);
void	update_declare_pwd(t_shell *shell, char *pwd_str, char *o_pwd_str);

//utils_2.c
int		cmp_str(char *s1, const char *s2);
int		count_args(char **args);
int		strcmp_ms(char *s1, char *s2);
void	prep_declare(t_shell *shell);
void	check_redir_faults(t_shell *shell);
//utils_3.c
char	*add_value_quotes(char *str, int var);
void	sort_declare(t_shell *shell);
int		scan_env(t_shell *shell, char *str);
int		scan_declare(t_shell *shell, char *str);
int		scan_declare_2(t_shell *shell, char **tmp, char *str, int j);

//utils_4.c
char	*ft_getenv(char *key, char **env);
void	adjust_lexer_redir(t_shell *shell);
void	check_final_lexer(t_shell *shell);
int		find_redir(char *str);
int		ft_memcmp_ms(const void *s1, const void *s2);

//utils_5.c
char	**ft_split_ms(const char *s, char c);

//utils_6.c
void	exit_shell(t_shell *shell, char *msg, int exit_status);
bool	strcmp_msn(char *s1, char *s2);
void	invalid_identifer(char *var_name);
bool	unexpected_token(char token);
bool	ft_isnum_bool(char *str);

//utils_7.c
size_t	exec_size(t_exec *exec);
char	*ft_strjoin_msn(char *s1, char *s2);
int		get_token_count_ms(char **token);
char	*ft_strjoin_ms(char *s1, char *s2);
void	adjust_token_values(t_shell *shell);

#endif
