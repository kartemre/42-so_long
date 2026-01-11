/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:56:42 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 18:45:39 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	process_lines(const char *buf, size_t len, t_parse *p)
{
	size_t	i;
	size_t	line_start;

	p->r = 0;
	i = 0;
	line_start = 0;
	p->first_len = -1;
	while (i < len)
	{
		if (buf[i] == '\n')
		{
			p->grid[p->r++] = copy_line(buf, line_start, i);
			if (p->first_len < 0)
				p->first_len = (int)(i - line_start);
			line_start = i + 1;
		}
		i++;
	}
	if (line_start < len)
	{
		p->grid[p->r++] = copy_line(buf, line_start, len);
		if (p->first_len < 0)
			p->first_len = (int)(len - line_start);
	}
}

static char	**split_to_lines(const char *buf, size_t len, int *rows, int *cols)
{
	t_parse	p;

	*rows = count_lines(buf, len);
	p.grid = (char **)ft_malloc(sizeof(char *) * (*rows));
	process_lines(buf, len, &p);
	if (p.first_len < 0)
		*cols = 0;
	else
		*cols = p.first_len;
	return (p.grid);
}

static char	*expand_buffer(char *buf, size_t len, size_t *cap)
{
	char	*nb;

	*cap *= 2;
	nb = (char *)ft_malloc(*cap);
	memcpy(nb, buf, len);
	free(buf);
	return (nb);
}

static char	*read_file(int fd, size_t *out_len)
{
	t_read	r;

	r.cap = 4096;
	r.len = 0;
	r.buf = (char *)ft_malloc(r.cap);
	while (1)
	{
		if (r.cap - r.len < 2048)
			r.buf = expand_buffer(r.buf, r.len, &r.cap);
		r.n = read(fd, r.buf + r.len, r.cap - r.len);
		if (r.n < 0)
		{
			free(r.buf);
			return (NULL);
		}
		if (r.n == 0)
			break ;
		r.len += (size_t)r.n;
	}
	*out_len = r.len;
	return (r.buf);
}

int	map_load_fd(int fd, t_map *out)
{
	char	*buf;
	size_t	len;

	len = 0;
	buf = read_file(fd, &len);
	if (!buf)
		return (-1);
	if (len == 0)
	{
		free(buf);
		return (-1);
	}
	out->grid = split_to_lines(buf, len, &out->rows, &out->cols);
	free(buf);
	return (0);
}
