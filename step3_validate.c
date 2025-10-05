/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step3_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:40:04 by ekart             #+#    #+#             */
/*   Updated: 2025/10/05 13:37:09 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

typedef struct s_map {
    char **grid;
    int rows;
    int cols;
}   t_map;

typedef struct s_counts {
    int c;
    int e;
    int p;
}   t_counts;

static int rowlen(const char *s)
{
    int n = 0;
    while (s && s[n]) n++;
    return n;   
}

int validate_rect_charset_counts(const t_map *m, t_counts *out, const char **err_msg)
{
	int r;
	int c;
	t_counts cnt = {0, 0, 0};
	if (!m || m->rows <= 0 || m->cols <= 0)
	{
		if (err_msg)
			*err_msg = "empty or invalid map dimensions";
		return (0);
	}
	r = 0;
	while (r < m->rows)
	{
		const char *row = m->grid[r];
		if (rowlen(row) != m->cols)
		{
			if (err_msg)
				*err_msg = "map is not rectangular";
            return 0;
		}
		c = 0;
		while (row[c])
		{
			char ch = row[c];
			if (ch != '0' && ch != '1' && ch != 'C' && ch != 'E' && ch != 'P')
			{
				if (err_msg)
					*err_msg = "map contains invalid character (allowed: 01CEP)";
				return 0;
			}
			if (ch == 'C')
				cnt.c++;
			else if (ch == 'E')
				cnt.e++;
			else if (ch == 'P')
				cnt.p++;
			c++;
		}
		r++;
	}
	if (cnt.e != 1) {
        if (err_msg) *err_msg = "map must contain exactly 1 E (exit)";
        return 0;
    }
    if (cnt.p != 1) {
        if (err_msg) *err_msg = "map must contain exactly 1 P (player)";
        return 0;
    }
    if (cnt.c < 1) {
        if (err_msg) *err_msg = "map must contain at least 1 C (collectible)";
        return 0;
    }
    if (out) *out = cnt;
    return 1;
}