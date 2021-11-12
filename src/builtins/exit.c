/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:18:45 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/05 11:45:13 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_digit_str(char *s, t_var **data)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (!ft_isdigit(s[i]) && ((s[0] != '-' && i == 0) || i > 0))
		{
			write(1, "minishell: exit: ", 17);
			write(1, s, ft_strlen(s));
			write(1, ": numeric argument required\n", 29);
			(*data)->status_exit = 255;
			return (0);
		}
		i++;
	}
	if (s == NULL || s[0] == '\0')
		return (0);
	return (1);
}

int	get_exit_status(char *cmd_line)
{
	long long	status;

	status = ft_atoi(cmd_line);
	if (ft_strlen(cmd_line) > 0 && status == 0)
		return (1);
	return (status % 256);
}

int	get_exit(char *cmd_line, t_var **data, char **argv)
{
	int	digit;
	int	argc;
	int	len;
	int	i;

	i = 0;
	digit = 1;
	len = ft_strlen_2d(argv);
	if (exists_pipes(cmd_line))
		return (write(1, "exit: too many arguments\n", 26));
	argc = get_argc(cmd_line);
	if (argc == -1)
		return (write(1, "minishell: invalid arguments\n", 30));
	if (len > 1)
		digit = is_digit_str(argv[1], data);
	if ((argc > 1 || len > 2) && digit)
		return (write(1, "exit: too many arguments\n", 26));
	(*data)->exit = 1;
	if (ft_strlen_2d(argv) == 2 && digit)
		(*data)->status_exit = get_exit_status(argv[1]);
	return (-2);
}
