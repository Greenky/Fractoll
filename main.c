/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 16:53:56 by vmazurok          #+#    #+#             */
/*   Updated: 2018/03/30 16:53:58 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void	fract_draw(t_grafx *gfx, int i)
{
	int			y;
	int			n;
	pthread_t	threads[THREADS_N];
	t_thread	t_data[THREADS_N];

	scaler(gfx, i, 0);
	n = 0;
	while (n++ < THREADS_N)
		t_data[n].gfx = NULL;
	y = 0;
	while (y < gfx->scr_size)
	{
		n = 0;
		while (n < THREADS_N && y + n < gfx->scr_size)
		{
			t_data[n].gfx = gfx;
			t_data[n].y = y + n;
			pthread_create(&(threads[n]), NULL, calculator, &(t_data[n]));
			n++;
		}
		joyner(threads, gfx, y);
		y += THREADS_N;
	}
	n = 0;
	mlx_put_image_to_window(gfx->mlx, gfx->win, gfx->img, 0, 0);
}

int		arrow_movement(int key, t_grafx *gfx)
{
	if (key == 124)
	{
		gfx->max_map_x += 0.01 / gfx->scale;
		gfx->min_map_x += 0.01 / gfx->scale;
	}
	else if (key == 123)
	{
		gfx->max_map_x -= 0.01 / gfx->scale;
		gfx->min_map_x -= 0.01 / gfx->scale;
	}
	else if (key == 125)
	{
		gfx->max_map_y += 0.01 / gfx->scale;
		gfx->min_map_y += 0.01 / gfx->scale;
	}
	else if (key == 126)
	{
		gfx->max_map_y -= 0.01 / gfx->scale;
		gfx->min_map_y -= 0.01 / gfx->scale;
	}
	fract_draw(gfx, 0);
	return (0);
}

int		key_press(int key, t_grafx *gfx)
{
	int i;

	i = 0;
	if (key == 53)
	{
		free(gfx);
		exit(0);
	}
	else if (key == 51)
	{
		gfx->scale = 1;
		i = 2;
	}
	else if (key == 49)
		gfx->motion = !(gfx->motion);
	else if (key == 6 || key == 7)
	{
		gfx->color++;
		if (gfx->color > 4)
			gfx->color = 0;
	}
	fract_draw(gfx, i);
	return (0);
}

int		mouse_click(int key, int x, int y, t_grafx *gfx)
{
	gfx->m_x = x;
	gfx->m_y = y;
	if (key == 4 || key == 1)
	{
		gfx->scale *= 1.05;
		fract_draw(gfx, 1);
	}
	if (key == 5 || key == 2)
	{
		if (gfx->scale > 1)
			gfx->scale /= 1.05;
		fract_draw(gfx, -1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_grafx *gfx;

	if (argc < 2 || argv[1][0] < '1' || argv[1][0] > '8')
		exit(error_msg());
	if (!(gfx = (t_grafx *)malloc(sizeof(t_grafx))))
	{
		perror("Error");
		return (1);
	}
	put_params(gfx);
	gfx->scr_size = SCR_SIZE;
	gfx->type = argv[1][0];
	if (argv[1][0] == '5' || argv[1][0] > '6')
		julia(gfx);
	fract_draw(gfx, 0);
	mlx_mouse_hook(gfx->win, mouse_click, gfx);
	mlx_key_hook(gfx->win, key_press, gfx);
	mlx_hook(gfx->win, 2, (1L << 0), arrow_movement, gfx);
	mlx_hook(gfx->win, 17, (1L << 17), exit_x, gfx);
	mlx_loop(gfx->mlx);
}
