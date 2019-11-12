/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:15:04 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/12 21:23:07 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char			*start_selection(int argc, const char **argv)
{
	t_args		*list;
	char		*result;
	size_t		max_len;

	list = save_arguments(&max_len, argc, argv);
	make_fullscreen();
	//придумать, как обработать и куда вставить сигнал
	if (calculate_position(list, argc, max_len) == 1)
		output_arguments((const t_args*)list, (const t_args*)list);
	else
		message_resize();
	// if (delete_argument(list, list->prev->prev) == NULL)
	// 	list = NULL;
	result = read_commands(list);
	reset_terminal_mode();
	if (list != NULL)
		free_arguments(list);
	return (NULL); //correct
}

void			select_element(t_args *list)
{
	t_args		*underlined;

	underlined = find_list(list, 'u');
	if (underlined->selected == 0)
	{
		underlined->selected = 1;
		inverse_video_on();
	}
	else
	{
		underlined->selected = 0;
		inverse_video_off();
	}
	position_and_clear_element(underlined->x,
		underlined->y, underlined->len);
	output_element(underlined->arg);
	underlined = move_down_b(underlined, 1);
}
