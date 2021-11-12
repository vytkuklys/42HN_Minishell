/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:29:47 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/05 10:31:15 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
# include <termios.h>

typedef struct s_var
{
	char	**env;
	int		error;
	int		exit;
	int		pipes;
	int		status;
	int		rl_error;
	int		counter;
	int		status_exit;
}			t_var;

void	print_prompt(int prompt);
int		get_echo(char **argv);
int		get_whitespace(char *cmd_line);
int		add_slashes(char **quote, char *start, int *j, char quote_mark);
char	*free_str(char **str);
int		get_env(char *envp[]);
int		are_slashes_valid(char *s, t_var **data);
int		are_quotes_valid(char *cmd_line, t_var **data);
int		exists_pipes(char *cmd_line);
int		get_argc(char *cmd_line);
int		get_argv(char *cmd_line, char **argv, char **env);
int		get_end_of_quote_pos(char *str);
int		get_end_of_arg_pos(char *str);
int		get_exit(char *cmd_line, t_var **data, char **argv);
int		get_arg_len(char *cmd_line);
int		add_char_to_text(char **str, char *cmd_line, int *j, int i);
int		ft_export(char **argv, t_var **data);
int		print_export(char *envp[]);
void	free_array(char ***arr);
int		print_export_error(char *arg, int *flag, char *error);
int		is_char_escaped(char *cmd_line, int i);
int		are_slashes_even(char *cmd_line, int i);
int		ft_unset(char **argv, t_var **data);
int		does_variable_exist(char **env, char *arg);
int		expand_variable(char **arg, char **env, char quote, char *cmd_line);
int		get_dollar_num(const char *s);
int		ft_pwd(void);
int		ft_cd(char **cmd_line);
void	handle_arg_without_quotes(int *counted, int *argc);
int		handle_quotes(char *cmd_line, int *counted, int *argc, int i);
int		handle_spaces(char *cmd_line, int *counted, int i);
int		process_command_line(char **cmd_line, t_var **data);
int		free_data(t_var **data, char **cmd);
char	*print_prompts(void);
int		get_len(char *s1, char *s2);
int		check_pipes(char **cmd_line, t_var *data);
void	execute_cmd(char **argv, t_var **data);
int		execute_single_command(char ***argv, t_var **data, char **cmd_line);
char	**ft_split_pipe(char *s, char c, char *d);
int		**init_fds(int pipes);
void	close_fds(int pipes, int **fd);
void	free_fds(int pipes, int **fd);
int		check_absolute_command(char *argv, t_var **data);
int		check_command(char **argv, t_var **data);
char	**get_path(char *envp[]);
int		print_error_cmd(char *src);
void	pr_error(char *s1, char *s2);
int		pr_error2(char *s1, char *s2);
int		redirect_append(char ***argv, int pos);
int		count_heredocs(char **argv);
int		count_redirections(char **argv);
int		redirect_in(char ***argv, int pos);
int		redirect_out(char ***argv, int pos);
void	update_argv(char ***argv, char *redirection, int pos);
int		check_builtin_command(char *cmd);
int		execute_builtin_command(char **cmd_line, t_var **data, char *cmd);
void	free_argv(char ***argv);
void	execute_compound_commands(char ***argv, t_var **data, char **cmd_line);
char	*get_command(char *cmd_line, t_var **data);
int		check_relative_and_absolute(char **argv, t_var **data, char **cmd_line);
void	handle_heredoc(char ***argv, int pos);
int		count_pipes(char *cmd_line);
int		init_data(char **env, t_var **data, int argc, char **argv);
int		ft_status(t_var **data);
int		check_input(char **argv, t_var **data);
int		process_command_line(char **cmd_line, t_var **data);
void	process_signal(int signum);
int		throw_invalid_error(t_var **data);
int		modify_arg_in_env(char **env, char *arg);
int		does_export_var_exists(char **env, char *arg);
int		is_arg_valid(char *argv, int *flag);
int		set_signal_status(int val);
char	*get_arg(char *cmd_line, int len, char **env);
char	*trim_back(char *arg, int len);
int		get_exp_arg_len(char *cmd_line, char **env, int len);
int		changetermios(int toggle);
int		update_argv_args(char ***argv, char *cmd_line, t_var **data);
int		modify_argv(char ***argv, int *hash, t_var **data);
int		get_extra_line_count(char **argv, int line, int chr);
int		get_redirection_type(char *cmd_line, int index);
int		get_r_num(char *cmd_line);
char	**add_str_2(char ***argv, int line, int chr);
char	**add_str_3(char ***argv, int line, int chr);
char	**add_str_4(char ***argv, int line, int chr);
int		handle_redirections(char ***argv, int pos);
char	get_slash_type(char *cmd_line, int index);
void	init_signals(void);
int		is_in_quotes(char *cmd_line, int index);
char	**handle_split_at_pipes(char *cmd_line, t_var **data);
int		check_redirections(char **argv, t_var **data);

#endif
