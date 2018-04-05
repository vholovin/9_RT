/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_operations_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:10:39 by vholovin          #+#    #+#             */
/*   Updated: 2018/03/30 21:10:40 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	quat_len(t_quat q)
{
	return (sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w));
}

t_quat	quat_normalize(t_quat q)
{
	float length;
	float scale;

	length = quat_len(q);
	if (length != 1.0)
	{
		scale = (1.0f / sqrtf(length));
		q.x *= scale;
		q.y *= scale;
		q.z *= scale;
		q.w *= scale;
		return (q);
	}
	return (q);
}

t_quat	quat_conjugate(t_quat q)
{
	q.x = -q.x;
	q.y = -q.y;
	q.z = -q.z;
	q.w = -q.w;
	return (q);
}

t_quat	quat_mul(t_quat q1, t_quat q2)
{
	t_quat	res;

	res.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	res.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	res.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	res.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (res);
}

t_quat	quat_mul_vec3d(t_quat q, t_vec3 v)
{
	t_quat	res;

	res.w = -q.x * v.x - q.y * v.y - q.z * v.z;
	res.x = q.w * v.x + q.y * v.z - q.z * v.y;
	res.y = q.w * v.y + q.z * v.x - q.x * v.z;
	res.z = q.w * v.z + q.x * v.y - q.y * v.x;
	return (res);
}
