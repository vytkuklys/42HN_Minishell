/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:22:20 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/26 09:32:23 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_remainder(char **rem, char **line)
{
	char	*newline;
	char	*new_rem;
	int		len;

	newline = NULL;
	if (*rem)
	{
		new_rem = *rem;
		newline = ft_strchr(*rem, '\n');
		len = (ft_strlen(newline) - ft_strlen(*rem)) * -1;
		if (!newline)
			*line = ft_substr(*rem, 0, len);
		else if (len == ft_strlen(*rem))
			*line = ft_strdup("\n");
		else
			*line = ft_substr(*rem, 0, len + 1);
		if (!newline || ft_strlen(newline) == 1)
			*rem = NULL;
		else
			*rem = ft_substr(newline, 1, ft_strlen(newline));
		free(new_rem);
	}
	else
		*line = ft_calloc(1, 1);
	return (newline);
}

static char	*get_current_line(char **tmp, char **remainder)
{
	char	*newline;
	char	*line;
	char	*tmp_r;

	line = NULL;
	newline = ft_strchr(*tmp, '\n');
	if (newline)
	{
		line = ft_substr(*tmp, 0, ft_strlen(*tmp) - ft_strlen(newline) + 1);
		tmp_r = ft_strdup((*tmp) + (ft_strlen(*tmp) - ft_strlen(newline) + 1));
		free(*tmp);
		free(*remainder);
		*remainder = tmp_r;
		return (line);
	}
	else
	{
		if ((*tmp)[0] != '\0')
			line = ft_strdup(*tmp);
		free(*tmp);
		free(*remainder);
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*tmp;
	static char	*remainder;
	int			bytes;

	bytes = 1;
	check_remainder(&remainder, &tmp);
	while (bytes > 0 && !ft_strchr(tmp, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1 || fd < 0 || BUFFER_SIZE < 0)
		{
			free(tmp);
			tmp = NULL;
			return (NULL);
		}
		buffer[bytes] = '\0';
		tmp = ft_strjoin(&tmp, buffer);
	}
	if (remainder)
		tmp = ft_strjoin(&tmp, remainder);
	return (get_current_line(&tmp, &remainder));
}
