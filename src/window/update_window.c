/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvlad <mvlad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 11:39:16 by mvlad             #+#    #+#             */
/*   Updated: 2017/10/09 15:47:10 by mvlad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Clears screen.
** Sets render draw color to black and clears the window with it.
*/

void	clear_window(t_rt *r)
{
	SDL_SetRenderDrawColor(r->sdl->renderer, 0, 0, 0, 255);
	SDL_RenderClear(r->sdl->renderer);
}

/*
** Renders to the window, everything that was drawn before in the back buffer.
*/

void	render_present(t_rt *r)
{
	SDL_UpdateTexture(r->win->screen, NULL, &r->win->draw_buf[0], WIDTH * 4);
	SDL_RenderCopy(r->sdl->renderer, r->win->screen, NULL, NULL);
	if (r->togle_info == true)
	{
		refresh_gui(r);
		SDL_RenderCopy(r->sdl->renderer, r->img, NULL, &r->texr);
		SDL_RenderCopy(r->sdl->renderer, r->tex_message, NULL,
			&r->message_rect);
	}
	SDL_RenderPresent(r->sdl->renderer);
	bzero(r->win->draw_buf, WIDTH * HEIGHT * 4);
}
