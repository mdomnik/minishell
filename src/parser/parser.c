/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:28:57 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/19 17:53:44 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parser(t_shell *shell)
{
	group_redir(shell);
}

void group_redir(t_shell *shell)
{
	t_expand	*current;
	char		**io;
	int			file_num;

	current = shell->expand;
	if (!current)
		return ;
	io = (char **)ft_calloc((5), sizeof(char *));
	file_num = 0;
	while (current->next != NULL)
	{
		if (current->token != T_WORD && (current->next->token != T_WORD || current->next == NULL))
			free_err(ERR_SYNTAX, shell);
		if (current->token != T_WORD && current->next->token == T_WORD)
		{
			if (current->token == T_PIPE)
				break ;
			else if (current->token == T_LESSER || current->token == T_HEREDOC)
				io = pop_io(io, current->word, current->next->word, current->token);
			else if (current->token == T_GREATER || current->token == T_APPEND)
			{
				io = pop_io(io, current->word, current->next->word, current->token);
				file_num++;
			}
		}
		io[4] = NULL;
		current = current->next;
	}
	if (current->token != T_WORD && current->token != T_PIPE)
			free_err(ERR_SYNTAX, shell);
	group_files(shell, io, file_num);
}

void group_files(t_shell *shell, char **io, int file_num)
{
	t_expand	*current;
	char		**files;

	current = shell->expand;
	if (!current)
		return ;
	files = (char **)ft_calloc((file_num + 1), sizeof(char *));
	file_num = 0;
	while (current->next != NULL)
	{
		if (current->token != T_WORD && current->next->token == T_WORD)
		{
			if (current->token == T_PIPE)
				break ;	
			else if (current->token == T_GREATER || current->token == T_APPEND)
			{
				files[file_num] = ft_strdup(current->next->word);
				file_num++;
			}
		}
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	while(file_num > 0)
	{
		printf("files[%d]: %s\n", file_num, files[file_num - 1]);
		file_num--;
	}
	purge_redir(shell);
		free_double(io);
	free_double(files);
}

void	group_args(t_shell *shell, char **io, char **files)
{
	t_expand	*current;
	int			arg_num;
	char 		**args;
	
	current = shell->expand;
	arg_num = 0;
	while (current != NULL)
	{
		if (current->token == T_PIPE)
			break ;
		arg_num++;
		current = current->next;
	}
	args = (char **)ft_calloc((arg_num + 1), sizeof(char *));
	if (!args)
		free_err(ERR_MALLOC, shell);
	arg_num = 0;
	current = shell->expand;
	while (current != NULL)
	{
		if (current->token == T_PIPE)
			break ;
		args[arg_num] = ft_strdup(current->word);
		delete_node(shell, current);
		arg_num++;
		current = current->next;
	}
	while(arg_num > 0)
	{
		printf("args[%d]: %s\n", arg_num, args[arg_num - 1]);
		arg_num--;
	}
	print_expand(shell);
	free_double(io);
	free_double(files);
	free_double(args);
}
