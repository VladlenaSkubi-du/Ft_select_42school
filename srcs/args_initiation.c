/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_initiation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:31:44 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/07 18:31:21 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_args			*save_arguments(int argc, const char **argv)
{
	t_args		*list;
	t_args		*run;
	size_t		i;

	list = init_first_argument(argv[0]);
	run = list;
	i = 0;
	while (++i < argc)
	{
		init_next_argument(run, argv[i], i);
		run = run->next;
	}
	sort_arguments(list, argc);
	return (list);
}

t_args			*init_first_argument(const char *argument)
{
	t_args		*list;
	
	list = ft_xmalloc(sizeof(t_args));
	list->arg = ft_strdup(argument);
	list->len = ft_strlen(argument);
	list->next = list;
	list->prev = list;
	list->selected = 0;
	list->underline = 1;
	list->x = 0;
	list->y = 0;
	return (list);
}

void			init_next_argument(t_args *current,
					const char *argument, short flag)
{
	t_args		*tmp;
	t_args		*save;
	
	tmp = ft_xmalloc(sizeof(t_args));
	tmp->arg = ft_strdup(argument);
	tmp->len = ft_strlen(argument);
	tmp->selected = 0;
	tmp->underline = 0;
	tmp->x = 0;
	tmp->y = 0;
	if (flag == 1)
	{
		tmp->next = current;
		current->next = tmp;
		tmp->prev = current;
		current->prev = tmp;
	}
	else
	{
		save = current->next;
		tmp->next = save;
		current->next = tmp;
		tmp->prev = current;
		save->prev = tmp;
	}
}

void			sort_arguments(t_args *list, int total) //make sorting from ls
{
	
}