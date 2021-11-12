/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 01:02:31 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/04 15:34:08 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	nbr_of_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i);
}

static int	has_spaces(char *argv)
{
	int		i;
	int		flag;

	flag = 0;
	i = -1;
	while (argv[++i] != '\0')
		if (argv[i] == ' ')
			flag = 1;
	if (flag == 1)
	{
		write(1, "minishell: ", 12);
		write(1, argv, ft_strlen(argv));
		write(1, ": command not found: \n", 23);
	}
	return (flag);
}

int	get_echo(char **argv)
{
	int	i;
	int	n;

	if (argv == NULL || has_spaces(*argv))
		return (-3);
	n = 0;
	i = 1;
	if (nbr_of_args(argv) > 1)
	{
		if (!ft_strcmp(argv[i], "-n"))
		{
			n = 1;
			i++;
		}
		while (argv[i] != NULL)
		{
			write(1, argv[i], ft_strlen(argv[i]));
			if (argv[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
	}
	if (n == 0)
		write(1, "\n", 1);
	return (1);
}
