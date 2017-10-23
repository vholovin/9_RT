/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvlad <mvlad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 11:39:16 by mvlad             #+#    #+#             */
/*   Updated: 2017/10/18 17:13:12 by mvlad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	keyboard_core(t_rtv *rtv)
  {
  	if (SDL_KEYDOWN && rtv->sdl->key_state[SDL_SCANCODE_ESCAPE])
  		exit(0);
 	if (SDL_KEYDOWN && rtv->sdl->key_state[SDL_SCANCODE_UP])
 	{
//		t_cylinder *c;
//		c = rtv->scene->objects[0]->type;
//		c->a.x += 50;
//		c->b.x += 50;

//		float t = vec3_dot(&rtv->scene->cam.eye, &rtv->scene->cam.d);

		t_vec3d tmp = vec3_scale(0.06, &rtv->scene->cam.d);
		rtv->scene->cam.eye = vec3_add(&rtv->scene->cam.eye, &tmp);
		rtv->scene->cam.d = vec3_norm(rtv->scene->cam.eye);
//		rtv->scene->cam.eye.z += 0.04;

//		position += direction * speed
//		rtv->scene->cam.d.z

		clear_window(rtv);
		raytrace(rtv);
		render_present(rtv);
	}
	if (SDL_KEYDOWN && rtv->sdl->key_state[SDL_SCANCODE_DOWN])
	{
//		t_cylinder *c;
//		c = rtv->scene->objects[0]->type;
//		c->a.x -= 50;
//		c->b.x -= 50;
		rtv->scene->cam.eye.z -= 0.04;

		clear_window(rtv);
		raytrace(rtv);
		render_present(rtv);
	}
	if (SDL_KEYDOWN && rtv->sdl->key_state[SDL_SCANCODE_RIGHT])
	{
//		t_plane *p = rtv->scene->objects[0]->type;
//		p->normal.x += 50;

		rtv->scene->cam.eye.x -= 0.04;

		clear_window(rtv);
		raytrace(rtv);
		render_present(rtv);
	}
	if (SDL_KEYDOWN && rtv->sdl->key_state[SDL_SCANCODE_LEFT])
	{
		rtv->scene->cam.eye.x += 0.04;
//		t_plane *p = rtv->scene->objects[0]->type;
//		p->normal.x -= 50;

		clear_window(rtv);
		raytrace(rtv);
		render_present(rtv);
	}
}
