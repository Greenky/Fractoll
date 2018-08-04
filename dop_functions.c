/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:38:14 by vmazurok          #+#    #+#             */
/*   Updated: 2018/03/30 14:38:16 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void				pixel_add(t_grafx *gfx, int x, int y, unsigned int color)
{
	int bpp;
	int size_l;
	int end;
	int *buff;

	if (x >= 0 && x < gfx->scr_size && y >= 0 && y < gfx->scr_size)
	{
		buff = (int *)mlx_get_data_addr(gfx->img, &bpp, &size_l, &end);
		buff[(int)(gfx->scr_size) * y + x] = color;
	}
}

double				mapper(double x, double range_s, double range_f)
{
	if (range_f != range_s)
		return (x / SCR_SIZE * (range_f - range_s) + range_s);
	else
		return (range_s);
}

static unsigned int	color_v2(int n, t_grafx *g)
{
	unsigned int color;

	if (n < (17 * (g->scale > 1 ? g->scale : 1)))
	{
		color = (int)(n / (g->scale > 1 ? g->scale : 1)) * 5 * pow(16, 4);
		color += (int)(n / (g->scale > 1 ? g->scale : 1)) * 5;
	}
	else if (n > (17 * (g->scale > 1 ? g->scale : 1)) && n < (34 *
	(g->scale > 1 ? g->scale : 1)))
	{
		color = (int)(n / (g->scale > 1 ? g->scale : 1)) * 5 * pow(16, 2);
		color += (int)(n / (g->scale > 1 ? g->scale : 1)) * 5;
	}
	else
	{
		color = (int)(n / (g->scale > 1 ? g->scale : 1)) * 5 * pow(16, 2);
		color += (int)(n / (g->scale > 1 ? g->scale : 1)) * 5 * pow(16, 4);
		color += (int)(n / (g->scale > 1 ? g->scale : 1)) * 5;
	}
	return (color);
}

unsigned int		colorizer(int n, t_grafx *gfx)
{
	unsigned int color;

	color = 0;
	if (gfx->color == 0)
	{
		if (n < 12 * sqrt(gfx->scale))
			color = 0x0000FF + n / sqrt(gfx->scale) * 20;
		else if (n < 25 * gfx->scale)
			color = 0xFFFF00 - n / sqrt(gfx->scale) * 10 * pow(16, 2);
		else
			color = 0x8A2BE2 + n / gfx->scale * 5;
	}
	else if (gfx->color == 1)
		color = color_v2(n, gfx);
	else if (gfx->color == 2)
		color = n / gfx->scale * 5 * pow(16, 2);
	else if (gfx->color == 3)
		color = n / gfx->scale * 5;
	else
		color = n / gfx->scale * 5 * pow(16, 4);
	return (color);
}

void				put_params(t_grafx *gfx)
{
	if (!(gfx->mlx = mlx_init()))
	{
		perror("Error");
		exit(1);
	}
	if (!(gfx->win = mlx_new_window(gfx->mlx, SCR_SIZE, SCR_SIZE, "fractoll")))
	{
		perror("Error");
		exit(1);
	}
	if (!(gfx->img = mlx_new_image(gfx->mlx, SCR_SIZE, SCR_SIZE)))
	{
		perror("Error");
		exit(1);
	}
	gfx->key = 0;
	gfx->scale = 1;
	gfx->color = 0;
	gfx->motion = 1;
	gfx->m_x = 126;
	gfx->m_y = 370;
	def_map_size(gfx);
}
