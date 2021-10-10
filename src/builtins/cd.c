/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 05:00:26 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/10 05:20:23 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char *cmd_line, t_var **data)
{
	char	**argv;
	int		ch;

	argv = get_variables(cmd_line, data);
	if (argv == NULL)
		return (-1);
	fprintf(stderr, "%s", argv[1]);
	if (ft_strlen_2d(argv) != 2)
	{
		write(1, "cd: too many arguments", 23);
		return (-1);
	}
	ch = chdir(argv[1]);
	if (ch < 0)
		perror("cd");
	free_2d_array(&argv);
	return (0);
}
