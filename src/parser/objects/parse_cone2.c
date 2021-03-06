/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvlad <mvlad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 11:39:16 by mvlad             #+#    #+#             */
/*   Updated: 2018/03/31 19:07:07 by mvlad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		alloc_new_cone(t_rt *rt, int i)
{
	rt->scene->objects[i] = new_object(cone);
	rt->scene->objects[i]->type = new_cone();
	rt->scene->objects[i]->intersect = intersect_cone;
	rt->scene->objects[i]->normal = normal_cone;
}

t_bool		parse_cone_validation_value(cJSON *temp, char *str)
{
	cJSON *temp2;

	temp2 = cJSON_GetObjectItem(temp, str);
	if (!temp2)
		return (false);
	if (temp2->type != cJSON_Number)
		return (false);
	return (true);
}
