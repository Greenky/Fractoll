/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 19:03:55 by vmazurok          #+#    #+#             */
/*   Updated: 2018/01/12 19:04:01 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <errno.h>
# define SCR_SIZE 1000
# define THREADS_N 20

typedef struct	s_func
{
	char type;
	void (*f)(double *, double *, double, double);
}				t_func;

typedef struct	s_grafx
{
	void	*mlx;
	void	*win;
	void	*img;
	double	scr_size;
	int		key;
	char	motion;
	int		color;
	double	m_x;
	double	m_y;
	char	type;
	double	max_map_x;
	double	max_map_y;
	double	min_map_x;
	double	min_map_y;
	double	scale;
}				t_grafx;

typedef struct	s_thread
{
	int			y;
	t_grafx		*gfx;
}				t_thread;

int				error_msg(void);
void			m_brot(double *a, double *b, double a_copy, double b_copy);
void			m_brot3(double *a, double *b, double a_copy, double b_copy);
void			shipp(double *a, double *b, double a_copy, double b_copy);
void			m_brot4(double *a, double *b, double a_copy, double b_copy);
void			m_brot5(double *a, double *b, double a_copy, double b_copy);
void			pixel_add(t_grafx *gfx, int x, int y, unsigned int color);
double			mapper(double x, double range_s, double range_f);
unsigned int	colorizer(int n, t_grafx *gfx);
void			julia(t_grafx *gfx);
void			put_params(t_grafx *gfx);
void			def_map_size(t_grafx *gfx);
void			scaler(t_grafx *g, int i, double a);
int				count_n(int x, t_thread *t, int n, const t_func *f_c);
void			*calculator(void *t_data);
void			joyner(pthread_t *threads, t_grafx *gfx, int y);
int				j_count_n(int x, t_thread *t, int n, int type);
void			fract_draw(t_grafx *gfx, int i);
int				mouse_click(int key, int x, int y, t_grafx *gfx);
int				key_press(int key, t_grafx *gfx);
int				arrow_movement(int key, t_grafx *gfx);
int				exit_x(void *par);

#endif
