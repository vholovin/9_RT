/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvlad <mvlad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 11:39:16 by mvlad             #+#    #+#             */
/*   Updated: 2017/10/09 15:13:42 by mvlad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3		vec3_norm(t_vec3 v)
{
	t_vec3	unit_vector;

	unit_vector = vec3_scale((1 / vec3_len(v)), &v);
	return (unit_vector);
}

float		vec3_len(t_vec3 v)
{
	float len;

	len = sqrtf(vec3_dot(v, v));
	return (len);
}

t_vec3		vec3_add3(t_vec3 a, t_vec3 b, t_vec3 c)
{
	t_vec3 tmp;

	tmp.x = a.x + b.x + c.x;
	tmp.y = a.y + b.y + c.y;
	tmp.z = a.z + b.z + c.z;
	return (tmp);
}

t_vec3		set_vec3_q(t_quat q)
{
	t_vec3	new_v;

	new_v.x = q.x;
	new_v.y = q.y;
	new_v.z = q.z;
	return (new_v);
}
