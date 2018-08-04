/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_more_dop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:36:03 by vmazurok          #+#    #+#             */
/*   Updated: 2018/03/30 20:36:20 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void	def_map_size(t_grafx *gfx)
{
	if (gfx->type == '3')
	{
		gfx->max_map_x = 1;
		gfx->max_map_y = 1;
		gfx->min_map_x = -2.5;
		gfx->min_map_y = -1;
	}
	else
	{
		gfx->max_map_x = 2;
		gfx->max_map_y = 2;
		gfx->min_map_x = -2;
		gfx->min_map_y = -2;
	}
}

void	scaler(t_grafx *g, int i, double a)
{
	if (i == 1)
	{
		a = (g->max_map_x - g->min_map_x) * 0.8;
		g->max_map_x = mapper(g->m_x + (g->scr_size / 2.5), g->min_map_x,
		g->max_map_x);
		g->min_map_x = g->max_map_x - a;
		a = (g->max_map_y - g->min_map_y) * 0.8;
		g->max_map_y = mapper(g->m_y + (g->scr_size / 2.5), g->min_map_y,
		g->max_map_y);
		g->min_map_y = g->max_map_y - a;
	}
	else if (i == -1)
	{
		a = (g->max_map_x - g->min_map_x) / 0.8;
		g->max_map_x = mapper(g->m_x + (g->scr_size / 1.6666), g->min_map_x,
		g->max_map_x);
		g->min_map_x = g->max_map_x - a;
		a = (g->max_map_y - g->min_map_y) / 0.8;
		g->max_map_y = mapper(g->m_y + (g->scr_size / 1.6666), g->min_map_y,
		g->max_map_y);
		g->min_map_y = g->max_map_y - a;
	}
	else if (i == 2)
		def_map_size(g);
}

int		count_n(int x, t_thread *t, int n, const t_func *f_c)
{
	double	a;
	double	b;
	double	a_copy;
	double	b_copy;
	int		i;

	a = mapper(x, t->gfx->min_map_x, t->gfx->max_map_x);
	b = mapper(t->y, t->gfx->min_map_y, t->gfx->max_map_y);
	a_copy = a;
	b_copy = b;
	n = 0;
	while (n++ < (t->gfx->scale > 1 ? 50 * t->gfx->scale : 50))
	{
		i = -1;
		while (++i < 5)
			if (f_c[i].type == t->gfx->type)
				f_c[i].f(&a, &b, a_copy, b_copy);
		if (a * a + b * b >= 4)
			break ;
	}
	return (n);
}

void	*calculator(void *t_data)
{
	t_thread		*t;
	int				n;
	int				x;
	const t_func	f_c[] = {
		{'1', &m_brot},
		{'2', &m_brot3},
		{'3', &shipp},
		{'4', &m_brot4},
		{'6', &m_brot5}
	};

	t = (t_thread *)t_data;
	x = 0;
	while (x < t->gfx->scr_size)
	{
		if (t->gfx->type != '5' && t->gfx->type < '7')
			n = count_n(x, t, n, f_c);
		else
			n = j_count_n(x, t, n, t->gfx->type);
		pixel_add(t->gfx, x, t->y, colorizer(n, t->gfx));
		x++;
	}
	pthread_exit(0);
	return (NULL);
}

void	joyner(pthread_t *threads, t_grafx *gfx, int y)
{
	int n;

	n = 0;
	while (n < THREADS_N && y + n < gfx->scr_size)
	{
		pthread_join(threads[n], NULL);
		n++;
	}
}
