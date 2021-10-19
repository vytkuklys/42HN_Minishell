/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:13:23 by julian            #+#    #+#             */
/*   Updated: 2021/10/19 19:16:45 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	***fill_argv(char ***argv, char **split_at_pipe, t_var **data)
{
	int	i;
	int	argc;

	i = -1;
	while (++i <= (*data)->pipes)
	{
		argc = get_argc(split_at_pipe[i]);
		if (argc < 0)
		{
			printf("minishell: invalid command line arguments\n");
			(*data)->status = 1;
			return (NULL);
		}
		argv[i] = (char **)malloc(sizeof(char *) * (argc + 1));
		if (argv[i] == NULL)
			return (0);
		if (get_argv(split_at_pipe[i], argv[i], (*data)->env) == -1) //mem leak
			return (NULL);
	}
	argv[i] = NULL;
	return (argv);
}

static int	single_command(char ***argv, t_var *data, char **cmd_line)
{
	execute_single_command(argv, data);
	free_argv(argv);
	*cmd_line = ft_calloc(1, 1);
	if (*cmd_line == NULL) //add clean exit
		return (0);
	return (1);
}

static int	compound_command(char ***argv, t_var *data, char **cmd_line)
{
	execute_compound_commands(argv, data);
	free_argv(argv);
	*cmd_line = ft_calloc(1, 1);
	if (*cmd_line == NULL) //add clean exit
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
	argv = (char ***)malloc(sizeof(char **) * (*data)->pipes + 1);
	if (argv == NULL)
		return (0);
	split_at_pipe = ft_split_pipe(*cmd_line, '|', " ");
	if (split_at_pipe == NULL)
		return (0);
	argv = fill_argv(argv, split_at_pipe, data);
	if (argv == NULL)
		return (0);
	if ((*data)->pipes == 0)
		return (single_command(argv, data, cmd_line));
	else if ((*data)->pipes > 0)
		return (compound_command(argv, data, cmd_line));
	else
		return (1);
}
