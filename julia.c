/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:34:59 by vmazurok          #+#    #+#             */
/*   Updated: 2018/03/30 20:35:01 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

int			error_msg(void)
{
	write(2, "Usage:\n", 7);
	write(2, " 1 - Mandelbrot\n 2 - Cubic-Mandelbrot\n \
3 - Ship Fractoll\n 4 - Cvadro-Mandelbrot\n 5 - Juliya\n \
6 - Ultra-Mandelbrot\n 7 - Cubic-julia\n 8 - Cvadro-Julia\n", 150);
	return (1);
}

int			exit_x(void *par)
{
	free((t_grafx *)par);
	exit(1);
	return (0);
}

int			j_count_n(int x, t_thread *t, int n, int type)
{
	double			a;
	double			b;
	static double	a_copy;
	static double	b_copy;

	a = mapper(x, t->gfx->min_map_x, t->gfx->max_map_x);
	b = mapper(t->y, t->gfx->min_map_y, t->gfx->max_map_y);
	if (t->gfx->motion)
	{
		a_copy = mapper(t->gfx->m_x, -1, 1);
		b_copy = mapper(t->gfx->m_y, -1, 1);
	}
	n = 0;
	while (n++ < (t->gfx->scale > 1 ? 50 * t->gfx->scale : 50))
	{
		if (type == '5')
			m_brot(&a, &b, a_copy, b_copy);
		else
			type == '7' ? m_brot3(&a, &b, a_copy, b_copy) :
		m_brot4(&a, &b, a_copy, b_copy);
		if (sqrt(a * a + b * b) > 1 + sqrt(1 + 4 * sqrt(t->gfx->m_x *
		t->gfx->m_x + t->gfx->m_y * t->gfx->m_y)) / 2)
			break ;
	}
	return (n);
}

static int	mouse_move_hendler(int x, int y, t_grafx *gfx)
{
	if (gfx->motion)
	{
		gfx->m_x = x;
		gfx->m_y = y;
		fract_draw(gfx, 0);
	}
	return (0);
}

void		julia(t_grafx *gfx)
{
	fract_draw(gfx, 0);
	mlx_mouse_hook(gfx->win, mouse_click, gfx);
	mlx_key_hook(gfx->win, key_press, gfx);
	mlx_hook(gfx->win, 6, (1L << 6), mouse_move_hendler, gfx);
	mlx_hook(gfx->win, 2, (1L << 0), arrow_movement, gfx);
	mlx_hook(gfx->win, 17, (1L << 17), exit_x, gfx);
	mlx_loop(gfx->mlx);
}
