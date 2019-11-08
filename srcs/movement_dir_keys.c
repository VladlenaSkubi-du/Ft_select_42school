/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_dir_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:02:51 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/08 16:27:07 by sschmele         ###   ########.fr       */
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
	
	if (key == 4283163 && underlined->y > 0)
		underlined = move_up_A(underlined);
	else if (key == 4283163 && underlined->y == 0)
		bell_sound(underlined);
		
	if (key == 4348699 && underlined->y < term_lines)
		underlined = move_down_B(underlined);
	else if (key == 4348699 && underlined->y == term_lines)
		bell_sound(underlined);
		
	if (key == 4479771 && underlined->x > 0)
		underlined = move_left_D(underlined);
	else if (key == 4479771 && underlined->x == 0)
		bell_sound(underlined);
	
	if (key == 4414235 && underlined->x < limit_left)
		underlined = move_right_C(underlined);
	else if (key == 4414235 && underlined->x == limit_left)
		bell_sound(underlined);
}

/*
** Terminal capability `ec` needs only the length of the argument
** therefore, in tgoto we input the only parameter it needs on the 
** last position (instead of vpos)
*/

t_args			*move_down_B(t_args *under)
{
	under->underline = 0;
	position_and_clear_arg(under->x, under->y, under->len);
	ft_putstr_fd(under->arg, 1);
	under = under->next;
	under->underline = 1;
	under->y = 1; //делается иначе в расчете первоначальном
	//under->y = tgetnum("li"); //делается иначе в расчете первоначальном
	position_and_clear_arg(under->x, under->y, under->len);
	underline_on();
	ft_putstr_fd(under->arg, 1);
	underline_off();
	return(under);
}

t_args			*move_up_A(t_args *under)
{
	under->underline = 0;
	position_and_clear_arg(under->x, under->y, under->len);
	ft_putstr_fd(under->arg, 1);
	under = under->prev;
	under->underline = 1;
	position_and_clear_arg(under->x, under->y, under->len);
	underline_on();
	ft_putstr_fd(under->arg, 1);
	underline_off();
	return (under);
}

t_args			*move_right_C(t_args *under)
{
	printf("right\n");
	return (under);
}

t_args			*move_left_D(t_args *under)
{
	printf("left\n");
	return (under);
}