/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step2_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:06:54 by ekarr             #+#    #+#             */
/*   Updated: 2025/09/02 20:37:27 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_map {
	char **grid;
	int rows;
	int cols;
}	t_map;

static void *xmalloc(size_t n)
{
	void *p = malloc(n);
	if (!p)
		_exit(12);
	return p;
}

static int count_rows(const char *buf, size_t len)
{
	int	r;
	size_t	i;

	i = 0;
	r = 0;
	while (i < len)
	{
		if (buf[i] == '\n')
			r++;	
		i++;
	}
	if (len > 0 && buf[len - 1] != '\n')
		r++;
	return r;	
}

static char **split_lines(const char *buf, size_t len, int *out_rows, int *out_cols)
{
	int rows;
	int r;
	char **grid;
	size_t i;
	size_t line_start;
	int first_len;

	rows = count_rows(buf, len);
	grid = (char **)xmalloc(sizeof(char *) * rows);
	r = 0;
	i = 0;
	line_start = 0;
	first_len = -1;

	while (i <= len)
	{
		if(i == len || buf[i] == '\n')
		{
			size_t L = i - line_start;
			char *row = (char *)xmalloc(L + 1);
			if (L) memcpy(row, buf + line_start, L);
			row[L] = '\0';
			grid[r++] = row;
			if (first_len < 0) first_len = (int)L;
			line_start = i + 1;
		}
		i++;
	}
	*out_rows = rows;
	*out_cols = (first_len < 0) ? 0 : first_len;
	return grid;
}

int map_load_fd(int fd, t_map *out)
{
	size_t cap;
	size_t len;
	char *buf;

	cap = 4096;
	len = 0;
	buf = (char *)xmalloc(cap);
	while (1)
	{
		if (cap - len < 2048) { // yer daraldıysa büyüt
			cap *= 2;
			char *nb = (char *)xmalloc(cap);
			memcpy(nb, buf, len);
			free(buf);
			buf = nb;
		}
		ssize_t n = read(fd, buf +  len, cap - len);
		if (n < 0) { free(buf); return -1; }
		if (n == 0)
			break;
		len += (size_t)n;
	}
	out->grid = split_lines(buf, len, &out->rows, &out->cols);
	free(buf);
	return (0);
}

void map_free(t_map *m)
{
	int r;
	
	r = 0;
	if (!m || !m->grid)
		return;
	while (r < m->rows)
	{
		free(m->grid[r++]);
	}
	free(m->grid);
	m->grid = NULL;
}