/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calkuliren.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 16:05:07 by vmazurok          #+#    #+#             */
/*   Updated: 2018/03/30 16:05:42 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void	m_brot(double *a, double *b, double a_copy, double b_copy)
{
	double buff;

	buff = (*a) * (*a) - (*b) * (*b) + a_copy;
	(*b) = 2 * (*a) * (*b) + b_copy;
	(*a) = buff;
}

void	m_brot3(double *a, double *b, double a_copy, double b_copy)
{
	double buff;

	buff = (*a) * (*a) * (*a) - 3 * (*a) * (*b) * (*b) + a_copy;
	(*b) = 3 * (*a) * (*a) * (*b) - (*b) * (*b) * (*b) + b_copy;
	(*a) = buff;
}

void	shipp(double *a, double *b, double a_copy, double b_copy)
{
	double buff;

	buff = (*a) * (*a) - (*b) * (*b) + a_copy;
	(*b) = 2 * fabs((*a) * (*b) + b_copy);
	(*a) = fabs(buff);
}

void	m_brot4(double *a, double *b, double a_copy, double b_copy)
{
	double buff;

	buff = pow((*a), 4) + pow((*b), 4) - 6 * (*a) * (*a) * (*b) * (*b) +
	a_copy;
	(*b) = 4 * (*a) * (*b) * ((*a) * (*a) - (*b) * (*b)) + b_copy;
	(*a) = buff;
}

void	m_brot5(double *a, double *b, double a_copy, double b_copy)
{
	double buff;

	buff = pow((*a), 5) - 10 * pow((*a), 3) * (*b) * (*b) + 5 * (*a) *
	pow((*b), 4) + a_copy;
	(*b) = 5 * pow((*a), 4) * (*b) - 10 * (*a) * (*a) * pow((*b), 3) +
	pow((*b), 5) + b_copy;
	(*a) = buff;
}
