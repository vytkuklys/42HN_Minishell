/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:39:30 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/04 13:13:32 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	last_valid_char(char *cmd_line)
{
	int	i;

	i = ft_strlen(cmd_line);
	while (cmd_line[--i] == ' ')
		;
	return (cmd_line[i]);
}

void	dup_and_close(int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

static void	get_cmd_line(char **cmd_line, t_var *data)
{
	char	*tmp;

	while ((last_valid_char(*cmd_line) == '|') && data->rl_error != 1)
	{
		tmp = readline("> ");
		if (!tmp)
			break ;
		if (check_pipes(&tmp, data))
		{
			free (tmp);
			free (*cmd_line);
			data->rl_error = 1;
			*cmd_line = NULL;
			break ;
		}
		*cmd_line = ft_strjoin(cmd_line, tmp);
		free (tmp);
	}
}

int	handle_readline(char **cmd_line, t_var **data)
{
	ft_status(data);
	if (!*cmd_line || (*data)->exit)
		return (-1);
	if (check_pipes(cmd_line, *data))
		(*data)->rl_error = 1;
	get_cmd_line(cmd_line, *data);
	if (!ft_strcmp(*cmd_line, "") || !are_quotes_valid(*cmd_line, data)
		|| !are_slashes_valid(*cmd_line, data))
		(*data)->rl_error = 1;
	if (*cmd_line && **cmd_line)
		add_history(*cmd_line);
	if ((*data)->rl_error == 0)
		if ((!process_command_line(cmd_line, data) || (*data)->exit)
			&& (*data)->status != 1)
			return (-1);
	if ((*data)->exit)
		return (-1);
	free(*cmd_line);
	*cmd_line = NULL;
	(*data)->rl_error = 0;
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd_line;
	t_var	*data;
	int		fd[2];

	data = (t_var *)malloc(sizeof(t_var));
	if (!data)
		return (-1);
	init_data(env, &data, argc, argv);
	while (1)
	{
		changetermios(0);
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
		cmd_line = readline(print_prompts());
		if (data->status == 1)
			write(1, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 20);
		if (handle_readline(&cmd_line, &data) == -1)
			break ;
		dup_and_close(fd);
	}
	fd[0] = data->status_exit;
	free_data(&data, &cmd_line);
	return (fd[0]);
}
