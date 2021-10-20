/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:39:30 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/20 08:26:39 by julian           ###   ########.fr       */
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

static char	*get_cmd_line(char *cmd_line, t_var *data)
{
	char	*tmp;

	while ((last_valid_char(cmd_line) == '|') && data->rl_error != 1)
	{
		tmp = readline("> ");
		if (!tmp)
			break ;
		if (check_pipes(&tmp, data))
		{
			free (tmp);
			free (cmd_line);
			data->rl_error = 1;
			return (NULL);
		}
		cmd_line = ft_strjoin(&cmd_line, tmp);
		free (tmp);
	}
	return (cmd_line);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd_line;
	t_var	*data;

	data = (t_var *)malloc(sizeof(t_var));
	if (!data)
		return (-1);
	init_data(env, &data, argc, argv);
	while (1)
	{
		cmd_line = readline(print_prompts());
		if (!cmd_line)
			break ;
		if (check_pipes(&cmd_line, data))
			data->rl_error = 1;
		cmd_line = get_cmd_line(cmd_line, data);
		if (!ft_strcmp(cmd_line, ""))
			data->rl_error = 1;
		if (cmd_line && *cmd_line)
			add_history(cmd_line);
		if (data->rl_error == 0)
			if (!process_command_line(&cmd_line, &data) || data->exit)
				break ;
		free(cmd_line);
		cmd_line = NULL;
		ft_status(&data);
		data->rl_error = 0;
	}
	// free_data(&data, &cmd_line);
	return (0);
}
