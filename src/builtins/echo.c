/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 01:02:31 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/17 23:35:10 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_echo(int fd)
{
	char	*buff;

	if (fd == -1)
		return (-1);
	buff = NULL;
	while (1)
	{
		free(buff);
		buff = NULL;
		buff = get_next_line(fd);
		if (buff != NULL)
			write(1, buff, ft_strlen(buff));
		else
			break ;
	}
	return (0);
}

int	execute_echo(char **argv, char **env)
{
	int	id;
	int	result;

	id = fork();
	if (id == -1)
		return (-1);
	if (id == 0)
	{
		result = open("result.txt", O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (result == -1)
			return (-1);
		dup2(result, STDOUT_FILENO);
		close(result);
		execve("/bin/echo", argv, env);
		return (-1);
	}
	waitpid(id, NULL, 0);
	return (0);
}

int	get_echo(char **argv, t_var **data)
{
	if (argv == NULL || execute_echo(argv, (*data)->env) == -1)
		return (-1);
	if (!access("result.txt", R_OK))
		print_echo(open("result.txt", O_RDONLY));
	return (1);
}
