/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 01:02:31 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/03 02:41:42 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_echo_flag_set(char *arg)
{
	int		i;
	int		j;
	char	flag[3];

	i = 0;
	j = 0;
	while (arg[i] != '\0' && j < 2)
	{
		flag[j] = arg[i];
		j++;		
		i++;
	}
	flag[j] = '\0';
	if (!ft_strncmp(flag, "-n", 2) && arg[i] == '\0')
		return (1);
	return (0);
}

// int	process_whitespace(char *arg, int index)
// {
// 	while (index > 0)
// 	{
		
// 	}
// }

int	put_echo(char **argv)
{
	int i;
	int	j;
	int	flag;

	flag = is_echo_flag_set(argv[0]);
	i = flag;
	while (argv[i] != NULL)
	{
		if ((i > 1 && flag) || (i > 0 && flag == 0))
			write(1, " ", 1);
		j = 0;
		while (argv[i][j] != '\0')
		{
			// if (argv[i][j] == '\\' && ft_strchr(" \t\v\f\r\b", argv[i][j + 1]))
			// 	j += process_whitespace(argv[i], j);
			// else
				write(1, &argv[i][j], 1);
			j++;
		}
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}

char    *get_echo(char *cmd_line)
{
	char	**argv;
	int		argc;

	argc = get_argc(cmd_line);
	if (argc == -1)
		return ("minishell: invalid command line arguments \n");
	argv = (char **)malloc((argc + 1) * sizeof(char *));
	get_argv(cmd_line, argv);
	put_echo(argv);
	return (NULL);
}
