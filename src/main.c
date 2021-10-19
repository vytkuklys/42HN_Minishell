/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:39:30 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/19 12:39:31 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_command_line(char **cmd_line, t_var **data)
{
	int		i;
	char	***argv;
	int		argc;
	char	**split_at_pipe;

	if (!*cmd_line)
		return (1);
	if ((*data)->env == NULL)
		return (0);
	(*data)->pipes = count_pipes(*cmd_line);
	argv = (char ***)malloc(sizeof(char **) * (*data)->pipes + 1);
	if (argv == NULL)
		return (0);
	split_at_pipe = ft_split_pipe(*cmd_line, '|', " ");
	if (split_at_pipe == NULL)
		return (0);
	i = -1;
	while (++i <= (*data)->pipes)
	{
		argc = get_argc(split_at_pipe[i]);
		if (argc < 0)
		{
			printf("minishell: invalid command line arguments\n");
			return (0);
		}
		argv[i] = (char **)malloc(sizeof(char *) * (argc + 1));
		if (argv[i] == NULL)
			return (0);
		if (get_argv(split_at_pipe[i], argv[i], (*data)->env) == -1)//mem leak
			return (0);
	}
	argv[i] = NULL;
	if ((*data)->pipes == 0) // single command
	{
		execute_single_command(argv, data);
		free_argv(argv);
		*cmd_line = ft_calloc(1, 1);
		if (*cmd_line == NULL) //add clean exit
			return (0);
		return (1);
	}
	else if ((*data)->pipes > 0)
	{
		execute_compound_commands(argv, data);
		free_argv(argv);
		*cmd_line = ft_calloc(1, 1);
		if (*cmd_line == NULL) //add clean exit
			return (0);
		return (1);
	}
	else
		return (1); // compound commants -> ToDo
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd_line;
	char	*tmp;
	int		error;
    t_var   *data;

    data = (t_var *)malloc(sizeof(t_var));
	if (!data)
		return (-1);
    init_data(env, &data, argc, argv);
	error = 0;
	while (1)
	{
		cmd_line = readline(print_prompts());
		if (!cmd_line)
			break ;
		if (check_pipes(&cmd_line))
			error = 1;
		while ((cmd_line[ft_strlen(cmd_line) - 1] == '|') && error != 1)
		{
			tmp = readline("> ");
			if (!tmp)
				break ;
			if (check_pipes(&tmp))
			{
				free (tmp);
				free (cmd_line);
				error = 1;
				break ;
			}
			cmd_line = ft_strjoin(&cmd_line, tmp);
			free (tmp);
		}
		if (cmd_line && *cmd_line)
			add_history(cmd_line);
		if (error == 0)
			if (!process_command_line(&cmd_line, &data) || data->exit)
				break ;
		error = 0;
		free(cmd_line);
		cmd_line = NULL;
		// cmd_line = readline(print_prompts());
	}
	// free_data(&data, &cmd_line);
	return (0);
}
