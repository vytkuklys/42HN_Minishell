/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:13:23 by julian            #+#    #+#             */
/*   Updated: 2021/11/03 17:28:37 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_split_at_pipe(char **src)
{
	int	i;

	i = -1;
	while (src[++i] != NULL)
		free(src[i]);
	free(src);
}

static char	***fill_argv(char ***argv, char **split_at_pipe, t_var **data)
{
	int	i;
	int	argc;

	i = -1;
	while (++i <= (*data)->pipes)
	{
		argc = get_argc(split_at_pipe[i]);
		argv[i] = (char **)malloc(sizeof(char *) * (argc + 1));
		if (argv[i] == NULL)
			return (0);
		if (get_argv(split_at_pipe[i], argv[i], (*data)->env) == -1)
			return (NULL);
		update_argv_args(&argv[i], split_at_pipe[i], data);
	}
	argv[i] = NULL;
	free_split_at_pipe(split_at_pipe);
	return (argv);
}

static int	single_command(char ***argv, t_var **data, char **cmd_line)
{
	execute_single_command(argv, data, cmd_line);
	free_argv(argv);
	if (*cmd_line == NULL)
		return (0);
	return (1);
}

static int	compound_command(char ***argv, t_var **data, char **cmd_line)
{
	execute_compound_commands(argv, data, cmd_line);
	free_argv(argv);
	if (*cmd_line == NULL)
		return (0);
	return (1);
}

int	process_command_line(char **cmd_line, t_var **data)
{
	char	***argv;
	char	**split_at_pipe;

	if ((*data)->env == NULL)
		return (0);
	(*data)->pipes = count_pipes(*cmd_line);
	if ((*data)->pipes == -1)
		(*data)->status = 258;
	if ((*data)->pipes == -1)
		return (write(1
				, "minishell: syntax error :unexpected end of file\n", 49));
	argv = (char ***)malloc(sizeof(char **) * ((*data)->pipes + 2));
	if (argv == NULL)
		return (0);
	split_at_pipe = handle_split_at_pipes(*cmd_line, data);
	if (split_at_pipe == NULL)
		return (0);
	argv = fill_argv(argv, split_at_pipe, data);
	if (argv == NULL)
		return (0);
	if ((*data)->pipes == 0)
		return (single_command(argv, data, cmd_line));
	else if ((*data)->pipes > 0)
		return (compound_command(argv, data, cmd_line));
	return (1);
}
