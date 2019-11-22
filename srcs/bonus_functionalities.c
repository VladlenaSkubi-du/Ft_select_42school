/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_functionalities.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:20:32 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/20 15:21:45 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			bell_sound(void)
{
	char		buf[10];
	char		*buffer;

	buffer = buf;
	tputs(tgetstr("bl", &buffer), 1, ft_putint);
	buffer = buf;
}

void			print_type_dir(char type, char *arg)
{
	if (type == 'd')
		ft_putstr_fd("\033[1;36m", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\033[0m", 2);
}

void			make_tab_new_directory(t_args **dirs, int *level, int *flag)
{
	t_args		*under;
	char		*new_path;
	int			i;
	int			tmp;

	i = 1;
	under = find_list(dirs[*level], 'u');
	if (under->type != 'd')
	{
		bell_sound();
		return ;
	}
	make_fullscreen();
	new_path = ft_strjoin(dirs[*level]->path_head, under->arg);
	new_path = ft_strrejoin(new_path, "/");
	if (dirs[(*level) + i] != NULL)
	{
		printf("aaaaaaaaaaaa %s\n", new_path);
		while (dirs[(*level) + i] != NULL)
		{
			printf("aaaaaaaaaaaa %s\n", new_path);
			printf("aaaaaaaaaaaa %s\n", dirs[(*level) + i]->path_head);
			if ((tmp = ft_strcmp(dirs[(*level) + i]->path_head, new_path)) == 0)
				break ;
			i++;
		}
		if (dirs[(*level) + i] != NULL)
			(*level) = i;
	}
	if (dirs[(*level) + i] == NULL)
	{
		dirs[(*level) + i] = save_files(new_path);
		if (dirs[(*level) + i] == NULL)
		{
			bell_sound();
			return ;
		}
		(*level)++;
		free(new_path);
	}
	resize_monitor(dirs[*level], flag);
}

void			make_back_parent_directory(t_args **dirs, int *level, int *flag)
{
	if (*level > 0)
	{
		(*level)--;
		resize_monitor(dirs[*level], flag);
	}
	else
		bell_sound();
}