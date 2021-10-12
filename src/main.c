/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:39:30 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/12 14:15:51 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_pwd(char *cmd_line)
{
	char	*output;
	int		i;

	if (cmd_line == NULL) //add clean exit
		return (NULL);
	i = 0;
	while (cmd_line[i] != '\0')
	{
		if (cmd_line[i] != ' ')
			return ("pwd: too many arguments");
		i++;
	}
	output = getenv("PWD");
	return (output);
}

char	*get_command(char *cmd_line)
{
	int	i;

	i = 0;
	if (cmd_line == NULL)
		return (NULL);
	while (cmd_line[i] != ' ' && cmd_line[i] != '\0')
		i++;
	return (ft_substr(cmd_line, 0, i));
}

int	process_command_line(char **cmd_line, char **env)
{
	int		i;
	char	***argv;
	int		argc;
	char	**split_at_pipe;
	int		nbr_of_pipes;

	if (*env == NULL)
		return (0);
	nbr_of_pipes = exists_pipes(*cmd_line);
	argv = (char ***)malloc(sizeof(char **) * nbr_of_pipes + 1);
	if (argv == NULL)
		return (0);
	split_at_pipe = ft_split_pipe(*cmd_line, '|', " ");
	if (split_at_pipe == NULL)
		return (0);
	i = -1;
	while (++i <= nbr_of_pipes)
	{
		argc = get_argc(split_at_pipe[i]);
		if (argc == -1)
		{
			printf("minishell: invalid command line arguments\n");
			return (0);
		}
		argv[i] = (char **)malloc(sizeof(char *) * (argc + 1));
		if (argv[i] == NULL)
			return (0);
		if (get_argv(split_at_pipe[i], argv[i]) == -1)
			return (0);
	}
	argv[i] = NULL;
	if (nbr_of_pipes == 0) // single command
	{
		execute_single_command(argv, env);
		free(*cmd_line);
		free_argv(argv);
		*cmd_line = ft_calloc(1, 1);
		if (*cmd_line == NULL) //add clean exit
			return (0);
		return (1);
	}
	else if (nbr_of_pipes > 0)
	{
		execute_compound_commands(argv, env, nbr_of_pipes);
		free(*cmd_line);
		free_argv(argv);
		*cmd_line = ft_calloc(1, 1);
		if (*cmd_line == NULL) //add clean exit
			return (0);
		return (1);
	}
	else
		return (1); // compound commants -> ToDo
}

void	process_signal(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\b\b  ", 4);
		print_error_prompt();
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd_line;

	if (argc == 0 && argv == NULL)
		argc = 0;
	signal(SIGINT, process_signal);
	signal(SIGQUIT, process_signal);
	while ((cmd_line = readline(print_prompt())))
	{
		if (cmd_line && *cmd_line)
			add_history(cmd_line);
		if (check_pipes(&cmd_line))
		{
			free (cmd_line);
			continue;
		}
		if (!process_command_line(&cmd_line, env))
			break ;
	}
	free_str(&cmd_line);
	return (0);
}
