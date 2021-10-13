/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:29:47 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/13 04:20:07 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PROMPT 0
# define ERR0R_PROMPT 1
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

typedef struct s_var
{
	char	**history;
	char	**env;
	int		error;
}			t_var;

void	print_prompt(int prompt);
int		get_echo(char *cmd_line, t_var **data);
int		get_whitespace(char *cmd_line);
int		add_slashes(char **quote, char *start, int *j);
char	*free_str(char **str);
void	get_env(char *envp[]);
int		are_slashes_valid(char *cmd_line);
int		are_quotes_valid(char *cmd_line);
int		exists_pipes(char *cmd_line);
int		get_argc(char *cmd_line);
int		get_argv(char *cmd_line, char **argv, char **env);
int		get_end_of_quote_pos(char *str);
int		get_end_of_arg_pos(char *str);
int		get_exit(char *cmd_line);
int		get_arg_len(char *cmd_line);
int		add_char_to_text(char **str, char *cmd_line, int *j, int i);
int		init_data(char **env, t_var **data);
int		ft_export(char *cmd_line, t_var **data);
void	free_2d_array(char ***arr);
int		print_export_error(char *arg, int *flag, char *error);
int		is_char_escaped(char *cmd_line, int i);
int		are_slashes_even(char *cmd_line, int i);
int		ft_unset(char *cmd_line, t_var **data);
char	**get_variables(char *cmd_line, t_var **data);
int		does_variable_exist(char **env, char *arg);
int		expand_variable(char **arg, char **env, char quote);
int		ft_pwd(void);
int		ft_cd(char *cmd_line, t_var **data);
int		get_last_char_index(char *cmd_line);
void	handle_arg_without_quotes(int *counted, int *argc);
int		handle_quotes(char *cmd_line, int *counted, int *argc, int i);
int		handle_spaces(char *cmd_line, int *counted, int i);
int		process_command_line(char **cmd_line, t_var **data, char *cmd);
int		print_history(char **history);
int		add_cmd_to_history(char *cmd, t_var **data);
int		print_cmd_not_found(char *cmd);
int		free_data(t_var **data, char **cmd);


#endif
