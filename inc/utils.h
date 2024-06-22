/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:12:05 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/22 15:01:22 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

//prototyping shell struct
typedef struct s_shell	t_shell;

//gen_utils_1.c
char	**double_dup(char **str);
void	free_double(char **double_str);
int		ft_strlen_ms(char *s);
char	**add_delim_split(char *str, t_shell *shell);
char	*ft_strjoin_ms(char *s1, char *s2);

//gen_utils_2.c
int		cmp_str(char *s1, const char *s2);
int		count_args(char **args);
char	**append_cmd_front(t_shell *shell, char **args);
int		strcmp_ms(char *s1, char *s2);
void	prep_declare(t_shell *shell);

//gen_utils_3.c
char	*add_value_quotes(char *str, int var);
void	sort_declare(t_shell *shell);
int		scan_env(t_shell *shell, char *str);
int		scan_declare(t_shell *shell, char *str);
int		scan_declare_2(t_shell *shell, char **tmp, char *str, int j);

//gen_utils_4.c
char	*ft_getenv(char *key, char **env);
void	adjust_lexer_redir(t_shell *shell);
void	check_final_lexer(t_shell *shell);
void	raise_shlvl(t_shell *shell);
void	lower_shlvl(t_shell *shell);
int		find_redir(char *str);
int	ft_memcmp_ms(const void *s1, const void *s2);

//gen_utils_split.c
char	**ft_split_ms(const char *s, char c);

//utils
void	exit_shell(t_shell *shell, char *msg, int exit_status);
void	destroy(t_shell *shell);
void	free_d_lst(char **list);
bool	strcmp_msn(char *s1, char *s2);
bool	unexpected_token(char token);
// int		unset_var(char *var_name, t_envp **envp);
// t_envp	*envp_new_node(char *var_name, char *var_value, bool is_exported);
// t_envp	*envp_last(t_envp *node);
// void	envp_add_back(t_envp **envp, t_envp *new);
// char	*get_envp(char *var_name, t_envp **envp);
// char	*get_varvalue_envp(char *var_name, t_shell *shell);
size_t	exec_size(t_exec *exec);
bool	ft_isnum_bool(char *str);
char	*ft_strjoin_msn(char *s1, char *s2);
// void	envp_clean(t_envp **list);
void	exec_clean(t_exec **exec);
int	get_token_count_ms(char **token);

#endif
