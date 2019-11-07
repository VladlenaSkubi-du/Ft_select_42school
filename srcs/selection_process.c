/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:15:04 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/07 19:55:59 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char			*start_selection(int argc, const char **argv)
{
	t_args		*list;
	char		*result;

	list = save_arguments(argc, argv);
	make_fullscreen();
	position_and_output_arguments((const t_args*)list);
	if (delete_argument(list, list->prev->prev) == NULL)
		list = NULL;
	position_and_output_arguments((const t_args*)list);
	result = read_commands(list);
	reset_terminal_mode();
	if (list != NULL)
		clean_arguments(list);
	return (NULL); //correct
}