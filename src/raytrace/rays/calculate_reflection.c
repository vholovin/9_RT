/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_reflection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:29:03 by vholovin          #+#    #+#             */
/*   Updated: 2018/03/30 21:29:04 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		rotate_dir_reflection(t_rt *rt)
{
	t_vec3	tmp1;

	if (rt->calc->cur_power_ray > 0.01f)
	{
		tmp1 = vec3_scale(-2.0f * vec3_dot(rt->scene->ray.dir,
			rt->calc->intersect_normal), &rt->calc->intersect_normal);
		rt->scene->ray.dir = vec3_add(&rt->scene->ray.dir, &tmp1);
		rt->scene->ray.dir = vec3_norm(rt->scene->ray.dir);
		rt->calc->last_status_refract = false;
	}
	rt->calc->cur_power_ray *= rt->calc->cur_mat.reflection;
}

void			calculate_reflection(t_rt *rt, t_rgbap *c_refl)
{
	t_rt	*rt_reflection;

	rt_reflection = ft_copy(rt);
	rotate_dir_reflection(rt_reflection);
	calculate_ray(rt_reflection);
	rt_reflection->calc->color.red *= rt->calc->cur_mat.reflection;
	rt_reflection->calc->color.green *= rt->calc->cur_mat.reflection;
	rt_reflection->calc->color.blue *= rt->calc->cur_mat.reflection;
	*c_refl = rt_reflection->calc->color;
	ft_free(rt_reflection);
}
