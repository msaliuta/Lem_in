/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:18:14 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/17 07:49:14 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				linecpy(char **dst, char *src, char c)
{
	int		i;
	int		pos;

	i = -1;
	while (src[++i])
		if (src[i] == c)
			break ;
	pos = i;
	if (!(*dst = ft_strnew(i)))
		return (0);
	if (!(*dst = ft_strncat(*dst, src, i)))
		return (0);
	return (pos);
}

char			*adline(char **s1, char *s2)
{
	char	*str;
	char	*tmp;
	size_t	i;
	size_t	j;

	tmp = *s1;
	if (!tmp || !s2)
		return (NULL);
	str = ft_strnew(ft_strlen(tmp) + ft_strlen(s2));
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (tmp[++i])
		str[i] = tmp[i];
	while (s2[++j])
	{
		str[i] = s2[j];
		i++;
	}
	free(*s1);
	return (str);
}

int				result(t_list **file, char *buf, int fd, char **line)
{
	int		i;
	t_list	*tmp;
	char	*tpm;

	tmp = *file;
	while ((i = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[i] = '\0';
		if (!(tmp->content = adline((char**)&tmp->content, buf)))
			return (-1);
		if (ft_strchr(tmp->content, '\n'))
			break ;
	}
	if (i < BUFF_SIZE && !ft_strlen(tmp->content))
		return (0);
	if ((i = linecpy(line, tmp->content, '\n')) < (int)ft_strlen(tmp->content))
	{
		tpm = ft_strdup(tmp->content + i + 1);
		free(tmp->content);
		if (!tpm || ((tmp->content = tpm) && 0))
			return (-1);
	}
	else
		ft_strclr(tmp->content);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			*buf;
	static t_list	*list;
	t_list			*file;
	int				i;

	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 ||
	!(buf = (char*)malloc(BUFF_SIZE + 1)) || read(fd, buf, 0) < 0)
		return (-1);
	file = list;
	while (file)
	{
		if ((int)file->content_size == fd)
			break ;
		file = file->next;
	}
	if (!file)
	{
		file = ft_lstnew("", fd);
		ft_lstadd(&list, file);
		file = list;
	}
	i = result(&file, buf, fd, line);
	free(buf);
	return (i);
}
