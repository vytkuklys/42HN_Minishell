/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:29:47 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/30 23:44:29 by vkuklys          ###   ########.fr       */
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

void	print_prompt(int prompt);
char    *get_echo(char *cmd_line);
int     get_whitespace(char *cmd_line);
int     add_char_to_text(char **str, char *cmd_line, int *j);
int     add_slashes(char **quote, char *start, int *j);
int     ft_strrstr(const char *big, const char *lil);
char    *free_str(char *str);
void	get_env(char *envp[]);

#endif
