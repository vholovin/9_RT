/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:28:39 by vholovin          #+#    #+#             */
/*   Updated: 2018/03/30 21:33:24 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_set_fong(t_rt *rt, float intensity)
{
	int		coef_glow;
	float	fong;

	coef_glow = rt->calc->cur_mat.reflection * 100;
	fong = rt->calc->cur_mat.reflection * powf(intensity, coef_glow)
		* rt->calc->cur_power_ray;
	fong = (fong > 1.0f) ? 1.0f : fong;
	fong = (fong < 0.0f) ? 0.0f : fong;
	rt->calc->color.red += (rt->calc->cur_mat.diffuse.red
	* rt->calc->light.red * fong * rt->calc->shadow.red);
	rt->calc->color.green += (rt->calc->cur_mat.diffuse.green
	* rt->calc->light.green * fong * rt->calc->shadow.green);
	rt->calc->color.blue += (rt->calc->cur_mat.diffuse.blue
	* rt->calc->light.blue * fong * rt->calc->shadow.blue);
}

static void	ft_fong(t_rt *rt, t_vec3 v_light)
{
	t_vec3	v_position;
	float	intensity;

	v_position = vec3_sub(&rt->calc->old_start, &rt->calc->new_start);
	v_position = vec3_norm(v_position);
	intensity = 2.0f * vec3_dot(rt->calc->intersect_normal, v_light)
		* vec3_dot(rt->calc->intersect_normal, v_position)
		- vec3_dot(v_light, v_position);
	if (intensity >= 0.0f)
		ft_set_fong(rt, intensity);
}

static void	ft_lambert(t_rt *rt, t_light cur_light)
{
	t_vec3	v_light;
	float	lambert;

	v_light = vec3_sub(&cur_light.pos, &rt->calc->new_start);
	v_light = vec3_norm(v_light);
	lambert = vec3_dot(v_light, rt->calc->intersect_normal)
		* rt->calc->cur_power_ray;
	lambert = (lambert > 1.0f) ? 1.0f : lambert;
	lambert = (lambert < 0.0f) ? 0.0f : lambert;
	rt->calc->color.red += (rt->calc->cur_mat.diffuse.red
	* rt->calc->light.red * lambert * rt->calc->shadow.red);
	rt->calc->color.green += (rt->calc->cur_mat.diffuse.green
	* rt->calc->light.green * lambert * rt->calc->shadow.green);
	rt->calc->color.blue += (rt->calc->cur_mat.diffuse.blue
	* rt->calc->light.blue * lambert * rt->calc->shadow.blue);
	if (rt->scene->status_glossy == true)
		ft_fong(rt, v_light);
}

static void	calc(t_rt *rt, t_light cur_light, int i)
{
	t_vec3	v_dist;
	float	dist;

	while (i++ < cur_light.len + 1)
	{
		v_dist = vec3_sub(&cur_light.pos, &rt->calc->new_start);
		dist = sqrtf(vec3_dot(v_dist, v_dist));
		if (dist <= 0.0f
			&& vec3_dot(v_dist, rt->calc->intersect_normal) <= 0.0f)
			continue;
		calculate_illumination(rt, cur_light, v_dist, dist);
		calculate_shadow(rt, cur_light, v_dist, dist);
		ft_lambert(rt, cur_light);
		cur_light.pos = vec3_add(&cur_light.pos, &cur_light.dir);
	}
}

void		calculate_light(t_rt *rt)
{
	t_light	cur_light;
	t_vec3	mid_pos;
	int		i;

	rt->calc->i = -1;
	while (rt->calc->i++ < rt->scene->lits_n - 1)
	{
		cur_light = *rt->scene->lights[rt->calc->i];
		i = cur_light.len;
		if (cur_light.type == 2)
		{
			mid_pos = vec3_scale(cur_light.len / 2, &cur_light.dir);
			cur_light.pos = vec3_sub(&cur_light.pos, &mid_pos);
			cur_light.power /= (float)cur_light.len;
			i = 0;
		}
		calc(rt, cur_light, i);
	}
}
