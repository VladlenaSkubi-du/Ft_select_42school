/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:23:25 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/14 15:23:43 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				main(int argc, char **argv)
{
	char			*termtype;
	char			room_termtype[1024];

	if (!isatty(STDIN_FILENO))
		return (1);
	if (argc < 2 || (argv[1] = ft_strtrim(argv[1])) == NULL)
		return (usage());
	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(room_termtype, termtype) != 1)
		return (terminal_errors(0));
	if (terminal_init_start(argc - 1, &argv[1]) < 0)
		return (terminal_errors(1));
	return (0);
}

char			*main_start_selection(int argc, const char **argv)
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
	result = read_commands(&list, argc);
	reset_terminal_mode();
	// if (result != NULL)
	// {
	// 	ft_putendl_fd(result, 1);
	// 	free(result);
	// }
	// else
	// 	ft_putchar_fd('\n', 1);
	if (list != NULL)
		free_arguments(list);
	return (result);
}

char			*generate_selected_line(t_args *list, int argc, char *result)
{
	char		**pointers;
	size_t		i;
	size_t		j;
	int			total;

	total = 0;
	j = -1;
	pointers = find_selected(list, argc, &total, &j);
	if (total == 0)
		return (NULL);
	result = (char*)ft_xmalloc(total + 1 + (j - 1));
	i = -1;
	while (++i < j)
	{
		result = ft_strcat(result, pointers[i]);
		result = ft_straddsy(result, ' ');
	}
	result = ft_strcat(result, pointers[i]);
	free(pointers);
	return (result);
}

/*
** @*j and @total - all because of the norm, I'm sorry for that
*/

char			**find_selected(t_args *list, int argc, int *total, size_t *j)
{
	char		**pointers;
	t_args		*run;
	size_t		i;

	pointers = (char**)ft_xmalloc(sizeof(char*) * argc + 1);
	run = list;
	i = -1;
	while (++i < argc)
	{
		if (run->selected == 1)
		{
			*total += run->len;
			pointers[++(*j)] = run->arg;
		}
		run = run->next;
	}
	return (pointers);
}
