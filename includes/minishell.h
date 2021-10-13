/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:29:47 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/13 14:55:23 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PROMPT 0
# define ERR0R_PROMPT 1
# define TRUE 1
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

typedef struct s_op
{
	int	pipes;
	int	heredoc;
	int	append;
	int	redirect_int;
	int	redirect_out;
}			t_op;

char	*print_prompt(void);
void	print_error_prompt(void);
char	*get_echo(char *cmd_line, char **env);
int		get_whitespace(char *cmd_line);
int		add_char_to_text(char **str, char *cmd_line, int *j);
int		add_slashes(char **quote, char *start, int *j);
int		ft_strrstr(const char *big, const char *lil);
char	*free_str(char **str);
void	get_env(char *envp[]);
int		are_slashes_valid(char *cmd_line);
int		are_quotes_valid(char *cmd_line);
int		exists_pipes(char *cmd_line);
int		get_argc(char *cmd_line);
int		get_argv(char *cmd_line, char **argv);
int		get_end_of_quote_pos(char *str);
int		get_end_of_str_pos(char *str);
char	*get_exit(char *cmd_line);
int		get_arg_len(char *cmd_line);
int		add_char_to_text(char **str, char *cmd_line, int *j);
int		check_pipes(char **cmd_line);
void	execute_single_command(char ***argv, char *envp[]);
void	execute_cmd(char **command, char *envp[]);
int		check_command(char **argv, char *envp[]);
char	**get_path(char *envp[]);
int		print_error_cmd(char *src);
void	exit_failure(char **path, char **cmd_n);
void	free_array(char **src);
void	execute_compound_commands(char ***argv, char *envp[], int pipes);
void	close_fds(int pipes, int fd[][2]);
void	initialize_operators(t_op *op);
int		check_builtin_command(char *cmd);
char	*get_command(char *cmd_line);
char	*get_pwd(char *cmd_line);
int		execute_builtin_command(char **argv, char *env[]);
int		ft_pwd(void);
char	*trim_pipes(char *src);
char	**ft_split_trim2(char const *s, char c, char *d);
void	pr_error(char *s1, char *s2);
void	get_redirections(t_op *op, char *s);
char	*trim_pipes(char *src);
char	**ft_split_pipe(char *s, char c, char *d);
void	free_argv(char ***argv);
int		exists_red_out(char **s);
int		exists_red_in(char **s);
int		exists_red_append(char **s);
int		exists_red_heredoc(char **s);
void	prepare_execution(char **argv, char *envp[]);
char	**redirect_heredoc(char **argv);
char	**redirect_in(char **argv);
char	**redirect_append(char **argv);
char	**redirect_out(char **argv);

#endif
