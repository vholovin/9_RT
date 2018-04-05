/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:19:07 by vholovin          #+#    #+#             */
/*   Updated: 2018/03/30 21:20:13 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_rgba	set_pixel_color(t_rt *rt, int steep)
{
	t_rgba color;

	color_filters(&rt->calc->sum_color, rt->scene->status_color);
	color.red = (unsigned char)MIN(rt->calc->sum_color.red
		/ (float)steep * 255.0f, 255.0f);
	color.green = (unsigned char)MIN(rt->calc->sum_color.green
		/ (float)steep * 255.0f, 255.0f);
	color.blue = (unsigned char)MIN(rt->calc->sum_color.blue
		/ (float)steep * 255.0f, 255.0f);
	color.alpha = SDL_ALPHA_OPAQUE;
	return (color);
}

static void		set_ray(t_rt *rt, float x, float y)
{
	t_vec3	xcomp;
	t_vec3	ycomp;
	t_cam	*c;

	c = &rt->scene->cam;
	rt->calc->cur_power_ray = 1.0;
	rt->calc->level_reflection = 0;
	rt->calc->level_transparent = 0;
	rt->calc->last_status_refract = false;
	xcomp = vec3_scale(((x * c->s.pixel_width) - c->s.half_width), &c->right);
	ycomp = vec3_scale(((y * c->s.pixel_height) - c->s.half_height), &c->up);
	rt->scene->ray.dir = vec3_norm(vec3_add3(c->forward, xcomp, ycomp));
	rt->scene->ray.pos = rt->scene->cam.pos;
}

void			calculate_ray(t_rt *rt)
{
	rt->calc->color.red = 0;
	rt->calc->color.green = 0;
	rt->calc->color.blue = 0;
	rt->calc->cur_obj = -1;
	if (rt->calc->cur_power_ray > 0.01f ||
		(rt->calc->level_reflection == rt->scene->max_level_reflection &&
		rt->calc->level_transparent == rt->scene->max_level_transparent))
	{
		if (object_intersect(rt) == true)
		{
			calculate_texture(rt);
			calculate_ambient_light(rt);
			if (rt->scene->lits_n != 0)
			{
				calculate_light(rt);
				calculate_reflect_refract(rt);
			}
		}
	}
}

static void		anti_aliasing(t_rt *rt, Uint16 x, Uint16 y)
{
	float	t_x;
	float	t_y;
	int		steep;

	steep = 0;
	t_y = y;
	while (t_y < y + 1)
	{
		t_x = x;
		while (t_x < x + 1)
		{
			set_ray(rt, t_x, t_y);
			calculate_ray(rt);
			rt->calc->sum_color.red += rt->calc->color.red;
			rt->calc->sum_color.green += rt->calc->color.green;
			rt->calc->sum_color.blue += rt->calc->color.blue;
			t_x += 1.0f / rt->scene->aa;
			steep++;
		}
		t_y += 1.0f / rt->scene->aa;
	}
	rt->calc->pixel_color = set_pixel_color(rt, steep);
}

void			*raytrace(void *arg)
{
	t_rt_pth	*rt_pth;
	t_rt		*rt;
	Uint16		x;
	Uint16		y;

	rt_pth = (t_rt_pth *)arg;
	rt = rt_pth->rt;
	y = 0;
	while (y++ < HEIGHT)
	{
		x = WIDTH * rt_pth->i / NB_THREAD;
		while (x++ < (WIDTH * (rt_pth->i + 1) / NB_THREAD))
		{
			rt->calc->sum_color.red = 0.0f;
			rt->calc->sum_color.green = 0.0f;
			rt->calc->sum_color.blue = 0.0f;
			anti_aliasing(rt, x, y);
			ft_draw_pixel(x, y, &rt->calc->pixel_color, rt->win->draw_buf);
		}
	}
	pthread_exit(0);
}
