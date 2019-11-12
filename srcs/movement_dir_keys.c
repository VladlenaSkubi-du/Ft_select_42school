/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_dir_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:02:51 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/12 21:20:39 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			make_movements(t_args *list, int key)
{
	t_args		*underlined;
	int			term_lines;
	int			term_columns;
	int			limit_left;

	underlined = find_list(list, 'u');
	term_lines = tgetnum("li");
	term_columns = tgetnum("co");
	limit_left = term_columns - underlined->len - 2; //check
	if (key == 4283163)
		underlined = move_up_a(underlined, 0);
	if (key == 4348699)
		underlined = move_down_b(underlined, 0);
	if (key == 4479771 && underlined->x > 0)
		underlined = move_left_d(underlined, 0);
	else if (key == 4479771 && underlined->x == 0)
		bell_sound(underlined);
	if (key == 4414235 && underlined->x < limit_left)
		underlined = move_right_c(underlined, 0);
	else if (key == 4414235 && underlined->x == limit_left)
		bell_sound(underlined);
}

/*
** Terminal capability `ec` needs only the length of the argument
** therefore, in tgoto we input the only parameter it needs on the
** last position (instead of vpos)
**
** @video can be equal to 0 - do not change the inverse video mode
** or one - turn off the inverse video mode.
*/

t_args			*move_down_b(t_args *under, int video)
{
	under->underline = 0;
	position_and_clear_element(under->x, under->y, under->len);
	output_element(under->arg);
	under = under->next;
	under->underline = 1;
	position_and_clear_element(under->x, under->y, under->len);
	if (under->selected == 1)
		inverse_video_on();
	else
		inverse_video_off();
	underline_on();
	output_element(under->arg);
	underline_off();
	return (under);
}

t_args			*move_up_a(t_args *under, int video)
{
	under->underline = 0;
	position_and_clear_element(under->x, under->y, under->len);
	output_element(under->arg);
	under = under->prev;
	under->underline = 1;
	position_and_clear_element(under->x, under->y, under->len);
	if (under->selected == 1)
		inverse_video_on();
	else if (under->selected == 0)
		inverse_video_off();
	underline_on();
	output_element(under->arg);
	underline_off();
	return (under);
}

t_args			*move_right_c(t_args *under, int video)
{
	printf("right\n");
	return (under);
}

t_args			*move_left_d(t_args *under, int video)
{
	printf("left\n");
	return (under);
}
