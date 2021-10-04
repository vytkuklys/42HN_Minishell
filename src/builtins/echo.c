/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 01:02:31 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/04 02:56:26 by vkuklys          ###   ########.fr       */
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

char    *get_echo(char *cmd_line, char **env)
{
	char	**argv;
	int		argc;

	argc = get_argc(cmd_line);
	if (argc == -1)
		return ("minishell: invalid command line arguments \n");
	argv = (char **)malloc((argc + 1) * sizeof(char *));
	get_argv(cmd_line, argv);
	execute_echo(argv, env);
	if (!access("result.txt", R_OK))
		print_echo(open("result.txt", O_RDONLY));
	else
		fprintf(stderr, "%s", "2");
	return (NULL);
}
